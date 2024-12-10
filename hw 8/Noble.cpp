//
// Created by Joy Wang on 11/22/2024.
// Noble cpp
//

#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    class Protector;
    // constructor
    Noble::Noble(const std::string& name) : name(name) {}
    // output operator for any Noble type
    ostream& operator<<(ostream &os, const Noble &noble) {
        os << noble.name << " has ";
        noble.display(os);
        return os;
    }
    // returns Noble name
    const string& Noble::getName() const {
        return name;
    }
    // returns status: alive or not
    bool Noble::isAlive() const {
        return alive;
    }
    // sets the Noble's death
    void Noble::die() {
        alive = false;
    }
    // a noble can call a battle on another noble and their army
    // the strengths of the armies are reduced after each battle
    // a noble dies when their army is dead, though battle results may vary
    void Noble::battle(Noble& opponent) {
        cout << getName() << " battles " << opponent.getName() << endl;
        double meStrong = getStrength();
        double oppStrong = opponent.getStrength();
        // both are alive, then battle
        if (isAlive() && opponent.isAlive()) {
            if (meStrong == oppStrong) {
                die();
                opponent.die();
                cout << "Mutual Annihilation: " << getName() << " and "
                     << opponent.getName() << " die at each other's hands" << endl;
            } else if (meStrong > oppStrong) {
                result(oppStrong);
                opponent.die();
                cout << getName() << " defeats " << opponent.getName() << endl;
            } else { // myStrength < theirStrength
                opponent.result(meStrong);
                die();
                cout << opponent.getName() << " defeats " << getName() << endl;
            }
        }
        // only one alive, strength is unchanged
        else if (isAlive() && !opponent.isAlive()) {
            cout << "He's dead, " << getName() << endl;
        } else if (!isAlive() && opponent.isAlive()) {
            cout << "He's dead, " << opponent.getName() << endl;
        }
        // both nobles are dead, there is no battle
        else {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }
    // loses a ratio of the strength after a battle
    // calculates the resulting strength, no return value
    void Noble::result(double oppStrong) {
        double strengthLeft = 1 - oppStrong / getStrength();
        setStrength(strengthLeft);
    }
    Lord::Lord(const string& name) : Noble(name) {}
    // the lord version of the display
    void Lord::display(std::ostream &os) const {
        os << "an army of size: " << army.size();
        // display their entire army
        for (size_t i=0; i<army.size(); ++i) {
            os << endl << "\t" << *army[i];
        }
    }
    // calculate total army strength after modifying army or battling
    // returns a double for strength of the "Lord of the Land"
    double Lord::getStrength() const {
        double totalStrength = 0;
        // cumulative strength of army
        for (const Protector* fighter: army) {
            totalStrength += fighter->getStrength();
        }
        return totalStrength;
    }
    // modify the strength of the army, thus changing the lord's strength
    // takes in a double, does not return a value
    void Lord::setStrength(double result) {
        // changes the strength by a ratio
        for (Protector *fighter: army) {
            double currentStrength = fighter->getStrength();
            fighter->setStrength(result * currentStrength);
        }
    }
    // try to add a protector to the army, returns true if successful
    bool Lord::hires(Protector &fighter) {
        size_t inArmy = findInArmy(fighter);
        // hiring only allowed if lord is alive and warrior isn't already hired
        if (isAlive() && inArmy == army.size() && !fighter.isHired()) {
            Protector *const newGuy = &fighter;
            army.push_back(newGuy);
            fighter.setEmployer(this);
            return true;
        }
        cout << getName() << " failed to hire " << fighter.getName() << endl;
        return false;
    }
    // remove a protector from the army, return true if successful
    bool Lord::fires(Protector &fighter) {
        size_t inArmy = findInArmy(fighter);
        // check if protector is hired and lord is alive
        if (isAlive() && inArmy < army.size()) {
            removeFromArmy(inArmy);
            cout << fighter.getName() << ", you don't work for me any more! "
                 << "-- " << getName() << "." << endl;
            return true;
        }
        cout << getName() << " failed to fire " << fighter.getName() << endl;
        return false;
    }
    // deletes a protector from army, can be called by fire or runaway methods
    void Lord::removeFromArmy(size_t idx) {
        army[idx]->setEmployer(nullptr);
        // maintains order of army by swapping left
        for (size_t i = idx; i < army.size()-1; ++i) {
            army[i] = army[i + 1];
        }
        // remove the last duplicate
        army.pop_back();
    }
    // find whether warrior exists in the army, search by address
    // returns the index of the location in army if successfully found
    size_t Lord::findInArmy(const Protector& protector) const {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &protector) {
                return i;
            }
        }
        return army.size();
    }
    // the whole army shows off their weird battle cries
    void Lord::defend() const {
        for (const Protector* fighter: army) {
            fighter->defend();
        }
    }
    // when lords die in battle, their whole army dies as well
    // interestingly, dead lords can still declare battle
    void Lord::die() {
        Noble::die();
        setStrength(0);
    }
    // the other type of Lord
    PersonWithStrengthToFight::PersonWithStrengthToFight
            (const string& name, double strength) :
            Noble(name), strength(strength) {}
    // display for "PersonWithStrengthToFight" type
    void PersonWithStrengthToFight::display(ostream &os) const {
        os << "strength: " << strength;
    }
    double PersonWithStrengthToFight::getStrength() const {
        return strength;
    }
    // they fight for themselves, but strength gets modified after battles too
    void PersonWithStrengthToFight::setStrength(double strengthRatio) {
        strength *= strengthRatio;
    }
    // barbaric battle cry
    void PersonWithStrengthToFight::defend() const  {
        cout << "Ugh!" << endl;
    }
    // all attributes set to 0 to indicate death
    void PersonWithStrengthToFight::die() {
        Noble::die();
        setStrength(0);
    }
}
