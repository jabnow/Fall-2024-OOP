//
// Created by Joy Wang on 11/22/2024.
// Protector cpp
//

#include <iostream>
#include <vector>

#include "Protector.h"
#include "Noble.h"
using namespace std;

namespace WarriorCraft {
    std::ostream& operator<< (std::ostream& os, const Protector& protector) {
        os << protector.name << " has strength " << protector.strength;
        return os;
    }
    Protector::Protector(const std::string& name, double strength) :
            name(name), strength(strength), employer(nullptr) {}
    const std::string& Protector::getName() const {
        return name;
    }
    double Protector::getStrength() const {
        return strength;
    }
    void Protector::setStrength(double result) {
        strength = result;
    }
    Lord* Protector::getEmployer() const {
        return employer;
    }
    void Protector::setEmployer(Lord* newEmployer) {
        employer = newEmployer;
    }
    // returns employment status of Protector
    bool Protector::isHired() const {
        return (employer != nullptr);
    }
    // protectors can remove themselves from the army
    // returns true if successful escape, false if not
    bool Protector::runaway() {
        // cerr? but it looks messed up in clion
        if (!employer) {
            cout << name << " has no employer." << endl;
            return false;
        } else { // use lord ptr to remove self from army
            cout << name << " flees in terror, abandoning his lord, " <<
            employer->getName() << endl;
            size_t idxInArmy = employer->findInArmy(*this);
            employer->removeFromArmy(idxInArmy);
            employer = nullptr;
            return true;
        }
    }
    // warrior constructor
    Warrior::Warrior(const std::string& name, double strength) :
            Protector(name, strength) {}
    // warrior battle cry
    void Warrior::defend () const {
        cout << getName() << " says: Take that in the name of my lord, " <<
        getEmployer()->getName() << endl;
    }
    // wizard battle cry
    Wizard::Wizard(const std::string& name, double strength) :
            Protector(name, strength) {}
    void Wizard::defend() const {
        cout << "POOF!" << endl;
    }
    // Archer constructor
    Archer::Archer(const std::string& name, double strength) :
            Warrior(name, strength) {}
    // Archer sfx
    void Archer::defend() const {
        cout << "TWANG!  ";
        Warrior::defend();
    }
    // Swordsman constructor
    Swordsman::Swordsman(const std::string &name, double strength) :
            Warrior(name, strength) {}
    // Swordsman sfx
    void Swordsman::defend() const {
        cout << "CLANG!  ";
        Warrior::defend();
    }
}