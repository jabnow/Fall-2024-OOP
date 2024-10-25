// FrogPrince.cpp
// 24F - Sec C

#include "Princess.h"
#include "FrogPrince.h"
#include <iostream>
#include <string>
using namespace std;

namespace Fantasy {

    //
    // FrogPrince implementation code
    //
    FrogPrince::FrogPrince(const string& name) : name(name), spouse(nullptr) {}

    const string& FrogPrince::getName() const { return name; }

    ostream& operator<<(ostream& os, const FrogPrince& rhs) {
        os << "FrogPrince: " << rhs.name;
        if (rhs.spouse != nullptr) {
            os << ", spouse: " << rhs.spouse->getName();
        }
        return os;
    }

    void FrogPrince::setSpouse(Princess* betrothed) { spouse = betrothed; }

}
