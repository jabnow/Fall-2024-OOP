/*
  Basics of Copy Control
  1.copy-control-B.cpp
 */

#include <iostream>
using namespace std;

class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs);
public:
    Thing(int x, const string& s) : name(s) {
        p = new int(x);
    }

    void setValue(int val) { *p = val; }
    int getValue() const { return *p; }

    //
    // Copy Control
    //

    //void cleanup() { delete p; }
    ~Thing() {
        delete p;
        // What about the string?
    } // destructor

    // Copy Constructor
    Thing(const Thing& anotherThing) : name(anotherThing.name) {
        // What about the string?
        p = new int(*anotherThing.p); // deep copy
    }

    // lhs = rhs
    // lhs.operator=(rhs)
    Thing& operator=(const Thing& rhs) {

        
        if (this != &rhs) { // 0. self-assignment check
            // 1. Free up whatever heap space the lhs is holding (destructor)
            // What about the string?
            delete p;

            // Copy constructor code
            // 2. allocate
            // 3. copying
            p = new int(*rhs.p);
            // What about the string?
            name = rhs.name;
        }
        // 4. return yourself
        return *this;
    }

private:
    int* p;
    string name;
};

ostream& operator<<(ostream& os, const Thing& rhs) {
    //return os << "Thing: " << *rhs.p;
    os << "Thing: " << *rhs.p << ", s: " rhs.s;
    return os;
}

// ===========  customer's code ==============

void doNothing(Thing x) {}

void simpleFunc() {
    Thing aThing(17, "John");
    doNothing(aThing);
    cout << aThing << endl;
    //aThing.cleanup();

    Thing something(6, "Mary");

    aThing = something;
    //operator=(aThing, something)
    //aThing.operator=(something);
}

int main() {
    simpleFunc();
    Thing* ptr = new Thing(100, "George");
    delete ptr;
}
