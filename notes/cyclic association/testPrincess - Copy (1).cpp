/*
    testPrincess.cpp
    Cyclic Association
    Sec Base
*/

#include <iostream>
#include <string>
using namespace std;

class FrogPrince;

class Princess {
    friend ostream& operator<<(ostream& os, const Princess& princess)
    {
	os << "Princess: " << princess.name;
	return os;
    } // op<< Princess
public:
    Princess(const string& name) : name(name) {}

    // void marries(FrogPrince& betrothed) {
    //     spouse = &betrothed;
    //     //betrothed.spouse = this;
    //     betrothed.setSpouse(this);
    // }
    void marries(FrogPrince& betrothed);

private:
    string name;
    FrogPrince* spouse;
}; // Princess

class FrogPrince {
    friend ostream& operator<<(ostream& os, const FrogPrince& frog)
    {
	os << "Frog Prince: " << frog.name;
	return os;
    } // op<< FrogPrince
public:
    FrogPrince(const string& name) : name(name) {}

    void setSpouse(Princess* betrothedPtr) { spouse = betrothedPtr; }

private:
    string name;
    Princess* spouse;
}; // FrogPrince

int main()
{
    Princess snowy("Snow White");
    cout << snowy << endl;
    FrogPrince froggy("Froggy");
    cout << froggy << endl;
    // snowy.marries(froggy);
    // cout << snowy << endl
    //      << froggy << endl;
} // main

void Princess::marries(FrogPrince& betrothed) {
    spouse = &betrothed;
    //betrothed.spouse = this;
    betrothed.setSpouse(this);
}
