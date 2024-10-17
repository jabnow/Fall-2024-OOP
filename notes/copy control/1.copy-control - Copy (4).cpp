/*
  Copy Control (start)
  CS2124 - 2024 Fall
  Inclass Sec E
 */

#include <iostream>
using namespace std;

// Thing class has just one field, a pointer an an int on the heap
class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs);
public:
    Thing(int x) { p = new int(x); }
    void setValue(int val) { *p = val; }
    int getValue() const { return *p; }

    //
    // Copy Control / BIG 3
    //
    //void cleanUp() { delete p; }
    ~Thing() { delete p; } // Destructor
    // Copy Constructor
    //Thing(Thing rhs) {
    Thing(const Thing& rhs) {
        //p = rhs.p;
        int val = *rhs.p;
        p = new int(val);
    }
    // aThing = another;
    // aThing.operator=(another); // Assignment operator
    Thing& operator=(const Thing& rhs) {
        // 0. checking for self assignment
        if (this != &rhs) {
            // 1. Free up
            delete p;

            // 2. Allocate & 3.Copy
            int val = *rhs.p;
            p = new int(val);
        }
        return *this;
    }


private:
    int* p;
};

void doNothing(Thing something) {}

void simpleFunc() {
    Thing aThing(17);
    cout << aThing << endl;
    //delete aThing.p;
    //aThing.cleanup();

    doNothing(aThing);

    Thing another(6);
    aThing = another;
    //operator=(aThing, another); // No, that's not a method
    aThing.operator=(another); // Assignment operator

    Thing yetAnother(aThing);
    Thing yetAnother2 = aThing;
}

int main() {
    simpleFunc();
}

ostream& operator<<(ostream& os, const Thing& rhs) { 
    os << *rhs.p;
    return os;
}
