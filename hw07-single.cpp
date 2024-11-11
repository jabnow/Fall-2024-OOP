/*
 hw07.cpp
 created by Joy Wang on 11/1/2024
 Warriors cont. (and runaways)
 COPY OF REC07.CPP
 */

// Comment out these two for the single file solution
//#include "Noble.h"
//#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& fighter);
public:
    Warrior(const string& name, double points);
    const string& getName() const;

    double getStrength() const;
    void setStrength(double result);

    bool getMaster() const;
    void setMaster(Noble* sir);

    bool runaway();
    bool isHired() const;
private:
    string warrior_name;
    double strength;
    Noble* master;
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& sir);
public:
    Noble(const string& name);
    const string& getName() const;
    bool getLife() const;
    double armyStrength() const;
    size_t getArmySize() const;

    bool hire(Warrior& fighter);
    bool fire(Warrior& fighter);
    bool remove(size_t& location);

    void resultingStrength(double winner, double loser);
    void battle(Noble& enemy);
    void rip();
    size_t find_warrior(const Warrior* warrior) const;

private:
    string noble_name;
    vector <Warrior*> army;
    bool is_alive;
};




int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

// all the operators
// overloaded operator for Warrior object
// permission to access private variables
ostream& operator<<(ostream& os, const Warrior& fighter){
    os << "\t" << fighter.warrior_name << ": " << fighter.strength;
    return os;
}
// overloaded operator for Noble object
// permission to access private variables
ostream& operator<<(ostream& os, const Noble& sir){
    os << sir.noble_name << " has an army of " << sir.army.size();
    for (const Warrior* someone : sir.army){
        if (someone){   // exists in vector
            os << endl;
            os << *someone;
        }
    }
    return os;
}

// Warrior class method definitions
Warrior::Warrior(const string& name, double points) :
        warrior_name(name),strength(points), master(nullptr){}
const string& Warrior::getName() const {return warrior_name;}
double Warrior::getStrength() const {return strength;}
void Warrior::setStrength(double result) {strength = result;}
// Warrior knows his employer
bool Warrior::getMaster() const {return master;}
void Warrior::setMaster(Noble* sir) {master = sir;}
// runaway method
// isHired method
bool Warrior::isHired() const {
    // Tarzan's Hire Status: false
    return master != nullptr;
}
bool Warrior::runaway(){
    // if warrior exists
    // if warrior is alive (or if lord is alive)
    // if warrior is in army (has a master)

    if (master == nullptr){
        return false;
    }

    if (!master->getLife()){
        cout << "noble is dead";
        return false;
    }
    if (strength ==0){
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


// Noble class method definitions
Noble::Noble(const string& name) : noble_name(name), is_alive(true){};
const string& Noble::getName() const {return noble_name;}
bool Noble::getLife() const {return is_alive;}
double Noble::armyStrength() const {
    double total=0;
    for (const Warrior* someone : army){
        total += someone->getStrength();
    }
    return total;
}
size_t Noble::getArmySize() const {return army.size();}
// this is how nobles add warriors to their army
// the output is whether hiring succeeded or failed
bool Noble::hire(Warrior& fighter) {
    // check if already hired and noble is not alive
    // else, hire and update vector
    if (fighter.getMaster() || !is_alive){
        cout << noble_name << " failed to hire " << fighter.getName()
             << endl;
        return false;
    }
    fighter.setMaster(this);
    army.push_back(&fighter);
    return true;
}
// this is how nobles fire warriors from their army
// pointer to fired warrior is removed not reassigned to avoid memory leak
// output is whether firing succeeded or failed
bool Noble::fire(Warrior& fighter) {
    if (!is_alive) {
        cout << noble_name << " failed to fire " << fighter.getName() << endl;
        return false;
    }
    size_t location = find_warrior(&fighter);
    if (location == army.size() || !remove(location)) {
        cout << noble_name << " failed to fire " << fighter.getName() << endl;
        return false;
    } else {
        cout << fighter.getName() << ", you don't work for me anymore! -- " <<
             noble_name << endl;
        // Set the warrior's master to nullptr to indicate
        // they are no longer hired
        fighter.setMaster(nullptr);
        return true;
    }
}
// now that warriors can runaway or get fired from the army
// once receiving a valid warrior location, they are removed
bool Noble::remove(size_t& location) {
    // called by the fire function
    // called by the runaway function
    if (location != army.size()){
        for (size_t i = location; i < army.size()-1; i++) {
            army[i] = army[i + 1];
        }
        army.pop_back();
        // remove pointers sir to fighter
        return true;
    }
    return false;
}

// this method calculates the total strength of the army after battle
// winner will lose a fraction of their strength, losers die
// no return value
void Noble::resultingStrength(double winner, double loser){
    for (Warrior* someone : army){
        if (winner == loser){
            someone->setStrength(0);
        } else {
            double update = someone->getStrength()*((winner - loser) / winner);
            if (update < 0) {update = 0;}   // no negatives
            someone->setStrength(update);
        }
    }
}
// a noble can call a battle on another noble and their army
// the strengths of the armies are reduced after each battle
// a noble dies when their army is dead, though battle results may vary
void Noble::battle(Noble& enemy){
    cout << noble_name << " battles " << enemy.noble_name << endl;
    // both nobles are alive
    // one noble is alive
    // both nobles are dead
    if (is_alive && enemy.is_alive){
        double self_points = armyStrength();
        double enemy_points = enemy.armyStrength();
        // if equally strong, both die
        // if not equally strong, do math per scenario
        if (self_points == enemy_points){
            rip();
            enemy.rip();
            cout << "Mutual Annihilation: " << noble_name << " and "
                 << enemy.noble_name << " die at each other's hands\n";
        } else if (self_points > enemy_points){
            resultingStrength(self_points, enemy_points);
            enemy.rip();
            cout << noble_name << " defeats "  << enemy.noble_name << endl;
        } else { // self_points < enemy_points
            resultingStrength(enemy_points, self_points);
            rip();
            cout << enemy.noble_name << " defeats " << noble_name << endl;
        }
    } else if (is_alive && !enemy.is_alive){
        cout << "He's dead, " << noble_name << endl;
    } else if (!is_alive && enemy.is_alive){
        cout << "He's dead, " << enemy.noble_name << endl;
    } else { // both dead
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    }
}
// this method represents a noble dying, so their entire army also dies
// there is no return value
void Noble::rip(){
    // worst case scenario both die, also avoids division by 0
    resultingStrength(1,1);
    is_alive = false;
}
// search through the army to return the position of a warrior
// will be called by remove method
size_t Noble::find_warrior(const Warrior* warrior) const {
    for (size_t i=0; i<army.size(); i++){
        if (army[i] == warrior){
            return i;
        }
    }
    return army.size();
}