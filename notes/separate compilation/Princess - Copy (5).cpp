// Princess.cpp
// 24F - Sec C

#include "Princess.h"
#include "FrogPrince.h"
#include <iostream>
#include <string>
using namespace std;

namespace Fantasy {

    //
    // Princess implementation code
    //
    Princess::Princess(const string& name) : name(name), spouse(nullptr) {}

    void Princess::marries(FrogPrince& betrothed) {
        spouse = &betrothed;
        betrothed.setSpouse(this);
    }

    const string& Princess::getName() const { return name; }

    ostream& operator<<(ostream& os, const Princess& rhs) {
        os << "Princess: " << rhs.name;
        if (rhs.spouse != nullptr) {
            os << ", spouse: " << rhs.spouse->getName();
        }
        return os;
    }

}
