#include <iostream>
using namespace std;

//cerr does the same thing 

class Base /*final*/ {
public:
    Base() { cerr << "Base() \n";}

    virtual ~Base() { cerr << "~Base() \n";} //if planned to be a base, always have a virtual destructor
                                                // put keyword "final" before class to claim a class to not be a base

    Base(const Base&) { cerr << "Base(const Base&)\n"; }

    Base& operator=(const Base& rhs) {
        cerr << "Base::operator=(const Base& rhs)\n";
        return *this;
    }
}; 

class Derived: public Base {
    public:
    Derived() : Base () { cerr << "Derived() \n";} //when called, initializes a base default constructor too

    ~Derived() { cerr << "~Derived() \n";} //first calls derived destructor and then the base class
                                            // doesn't matter what the base is doing

    //[Derived(const Derived&) : Base()] is that same as [Derived(const Derived&)]
    Derived(const Derived& rhs) : Base(rhs) /*<- principle of substitutability*/ { cerr << "Derived(const Derived&)\n"; }

    Derived& operator=(const Derived& rhs) {
        //*this Base::= rhs; not valid c++, can't qualify operator
        //(*this).Base::operator=(rhs); ugly!
        //this -> Base::operator=(rhs); Good!
        Base::operator=(rhs); //or you don't even need this ->

        cerr << "Derived::operator=(const Derived& rhs)\n";
        return *this;
    }

};

int main() {
    Derived der;
    Derived der2(der); //derived copy constructor, would call Base()'s copy constructor if not initlaized in derived
                        //Any derived constructor calls base first then the derived 
    cout << "===\n";

    cerr << "Derived der3 = der\n"
        << "-------------------\n";
    Derived der3 = der; //copy constructor, initializing der3 since it didn't exist before
    cout << "===\n";

    cerr << "der2 = der\n"
        << "-------------------\n"; //assignment operator 
    der2 = der;
    cout << "===\n";

    cerr << "Derived* p = new Derived();\n" << "delete p;\n" <<
         "-------------------\n";

    Derived* p = new Derived();
    delete p;
    cout << "===\n";

    cerr << "Base* bp = new Derived();\n" << "delete bp;\n" <<
         "-------------------\n";
    Base* bp = new Derived(); //derived destructor isn't getting called.... MEMORY LEAK
                                // want polymorphism, make virtual base destructor !
    delete bp;
    cout << "===\n";

}