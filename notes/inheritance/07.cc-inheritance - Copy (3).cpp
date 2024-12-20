/*
  07.cc-inheritance.cpp
  Copy Control with Inheritance
  Sec Base
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cerr << "Base()\n";
    }
    Base(const Base& rhs) {
        cerr << "Base(const Base&)\n";
    }
    //~Base() {
    virtual ~Base() {
        cerr << "~Base()\n";
    }
    Base& operator=(const Base& rhs) {
        cerr << "Base::operator=(const Base&)\n";
        return *this;
    }
};

// class Member {
// public:
//     Member() {
//         cerr << "Member()\n";
//     }
//     ~Member() {
//         cerr << "~Member()\n";
//     }
//     Member(const Member& rhs) {
//         cerr << "Member(const Member&)\n";
//     }
//     Member& operator=(const Member& rhs) {
//         cerr << "Member::operator=(const Member&)\n";
//         return *this;
//     }
// };

class Derived : public Base {
public:
    //Derived() { cerr << "Derived()\n"; }
    Derived() : Base() { cerr << "Derived()\n"; }

    // ~Derived()
    // {
        
    // }
    
    ~Derived() {
        cerr << "~Derived()\n";
    }

    //Derived(const Derived& rhs) {
    //Derived(const Derived& rhs) : Base() {
    Derived(const Derived& rhs) : Base(rhs) {
        cerr << "Derived(const Derived&)\n";
    }

    Derived& operator=(const Derived& rhs) {

        //*this Base::= rhs; // Not c++
        //*this Base::operator= rhs;
        //(*this).Base::operator=(rhs); // UGLY
        //this->Base::operator=(rhs); // Good!
        Base::operator=(rhs); // Also, Good!

        cerr << "Derived::operator=(const Derived&)\n";
        return *this;
    }
};

int main() {
    cerr << "Derived der;\n"
         << "------------\n";
    Derived der;
    cout << "===\n";

    cerr << "Derived der2(der);\n"
         << "------------------\n";
    Derived der2(der);
    cout << "===\n";

    cerr << "Derived der3 = der;\n"
         << "-------------------\n";
    Derived der3 = der;
    cout << "===\n";

    cerr << "der = der2;\n"
         << "-----------\n";
    der = der2;
    cout << "===\n";

    cerr << "Derived* p = new Derived();\n"
         << "delete p;\n"
         << "---------------------------\n";
    Derived* p = new Derived();
    delete p;
    cout << "===\n";

    cerr << "Base* bp = new Derived();\n"
         << "delete bp;\n"
         << "---------------------------\n";
    Base* bp = new Derived();
    delete bp;
    cout << "===\n";
}
