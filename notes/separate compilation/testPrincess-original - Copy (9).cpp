/*
    testPrincess-original.cpp
    Cyclic Association
    24F - Sec C
*/

#include <iostream>
#include <string>
using namespace std;

class FrogPrince;

class Princess {
    friend ostream& operator<<(ostream& os, const Princess& rhs);
public:
    Princess(const string& name);
    void marries(FrogPrince& betrothed);
    const string& getName() const;
private:
    string name;
    FrogPrince* spouse;
};

class FrogPrince {
    friend ostream& operator<<(ostream& os, const FrogPrince& rhs);
public:
    FrogPrince(const string& name);
    const string& getName() const;
    void setSpouse(Princess*);
private:
    string name;
    Princess* spouse;
};

int main() {
    Princess snowy("Snow White");
    cout << snowy << endl;
    FrogPrince froggy("Froggy");
    cout << froggy << endl;
    snowy.marries(froggy);
    cout << snowy << endl
        << froggy << endl;
}

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
