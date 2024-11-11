//
// Created by Joy Wang on 11/7/2024.
//

#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft {
    // overloaded operator for Warrior object
    // permission to access private variables
    ostream& operator<<(ostream& os, const Warrior& fighter){
        os << "\t" << fighter.warrior_name << ": " << fighter.strength;
        return os;
    }

    // Warrior class method definitions
    Warrior::Warrior(const string &name, double points) :
            warrior_name(name), strength(points), master(nullptr) {}

    const string &Warrior::getName() const { return warrior_name; }

    double Warrior::getStrength() const { return strength; }

    void Warrior::setStrength(double result) { strength = result; }

    // Warrior knows his employer
    bool Warrior::getMaster() const { return master; }

    void Warrior::setMaster(Noble *sir) { master = sir; }

    // runaway method
    // isHired method
    bool Warrior::isHired() const {
        // Tarzan's Hire Status: false
        return master != nullptr;
    }

    bool Warrior::runaway() {
        // if warrior exists
        // if warrior is alive (or if lord is alive)
        // if warrior is in army (has a master)

        if (master == nullptr) {
            return false;
        }

        if (!master->getLife()) {
            cout << "noble is dead";
            return false;
        }
        if (strength == 0) {
            cout << "warrior is dead";
            return false;
        }
        // find and remove Warrior from army
        // set pointers to null
        size_t location = master->find_warrior(this);
        if (location != master->getArmySize() && master->remove(location)) {
            cout << warrior_name << " flees in terror, abandoning his lord, "
                 << master->getName() << endl;
            master = nullptr;
            return true;
        }
        return false;
    }

}