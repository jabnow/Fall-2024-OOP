/*
  09.polyNonMember.cpp
  24F - Sec C
*/

#include <iostream>
using namespace std;

class Base {
public:
    virtual void display(ostream& os)  const {
        os << "Base"; 
    }
};

ostream& operator<<(ostream& os, const Base& rhs) {
    rhs.display(os);
    //os << "Base"; 
    return os;
}

class Derived : public Base {
public:
    virtual void display(ostream& os) const override {
        os << "Derived"; 
    }
};

// ostream& operator<<(ostream& os, const Derived& rhs) {
//     //os << "Derived";
//     rhs.display(os);
//     return os;
// }

// ======= Client Code =============

void func(const Base& base) {
    cout << base << endl;
    //base.operator<<(cout);
    //cout.operator<<(base);
    operator<<(cout, base);
}

int main() {
    Derived der;
    cout << der << endl;
    operator<<(cout, der);
    func(der);
}
