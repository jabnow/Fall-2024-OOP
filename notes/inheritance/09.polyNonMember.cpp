/*
  09.polyNonMember.cpp
  24F - Sec A
*/

#include <iostream>
using namespace std;

class Base {
public:
    virtual void display(ostream& os) const {
        os << "Base";
    }
};

// virtual ostream& operator<<(ostream& os, const Base& rhs) { // Can't
ostream& operator<<(ostream& os, const Base& rhs) {
    //os << "Base";
    rhs.display(os);
    return os;
}

class Derived : public Base { 
public:
     void display(ostream& os) const override {
        os << "Derived";
    }
};

// ostream& operator<<(ostream& os, const Derived& rhs) {
//     //    os << "Derived";
//     rhs.display(os);
//     return os;
// }

// ========= Client Code ==============

void func(const Base& base) {
    cout << base << endl;
    //base.operator<<(cout);
    //cout.operator<<(base);
    operator<<(cout, base);
}

int main() {
    Derived der;

    cout << der << endl;
    //operator<<(cout, der);

    func(der);
}
