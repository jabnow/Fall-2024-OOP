/*
  hw04_start.cpp
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& fighter);
public:
    Warrior(const string& name, const double points) :
    warrior_name(name),strength(points), is_hired(false){}
    const string& getName() const {return warrior_name;}
    int getStrength() const {return strength;}
    bool getJob() const {return is_hired;}
    void changeJob() {is_hired = !is_hired;}
    void setStrength(double result) {strength = result;}
private:
    string warrior_name;
    double strength;
    bool is_hired;
};
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& sir);
public:
    Noble(const string& name) : noble_name(name), is_alive(true){};
    const string& getName() const {return noble_name;}
    bool getLife() const {return is_alive;}
    double armyStrength() const {
        double total=0;
        for (const Warrior* someone : army){
            total += someone->getStrength();
        }
        return total;
    }
    // this is how nobles add warriors to their army
    // the output is whether hiring succeeded or failed
    bool hire(Warrior& fighter) {
        // check if already hired and noble is not alive
        // else, hire and update vector
        if (fighter.getJob() || !is_alive){
            cout << noble_name << " failed to hire " << fighter.getName()
            << endl;
            return false;
        }
        fighter.changeJob();
        army.push_back(&fighter);
        return true;
    }
    // this is how nobles fire warriors from their army
    // pointer to fired warrior is removed not reassigned to avoid memory leak
    // output is whether firing succeeded or failed
    bool fire(Warrior& fighter){
        // check if noble is alive and if is employer
        // else, find and remove &warrior in vector
        if (!is_alive){
            cout << noble_name << "failed to fire " <<
                 fighter.getName() << endl;
            return false;
        }
        bool was_fired = false;
        for (size_t i = 0; i < army.size(); i++){
            if (&fighter == army[i]){
                fighter.changeJob();
                cout << fighter.getName() << ", you don't work for me any more"
                                                 "! -- " << noble_name<< ".\n";
                // maintain order by shifting
                for (size_t j = i; j < army.size()-1; j++){
                    army[j]=army[j+1];
                }
                army.pop_back();
                was_fired = true;
            }
        }
//            if (was_fired == false) {
//                if (&fighter == army[i]){
//                    fighter.changeJob();
//                    cout << fighter.getName() << ", you don't work for me any more"
//                                                 "! -- " << noble_name<< ".\n";
//                    was_fired = true;
//                }
//            } else {
//                army[i-1] = army[i];
//            }
//        }
        if (!was_fired){
            cout << noble_name << "failed to fire " <<
                 fighter.getName() << endl;
        }
        return was_fired;
    }
    // this method calculates the total strength of the army after battle
    // pass in int for winner and loser strength due to int->double conversion
    // winner will lose a fraction of their strength, losers die
    // no return value
    void resultingStrength(double winner, double loser){
        for (Warrior* someone : army){
            double update = someone->getStrength() * ((winner - loser) / winner);
            someone->setStrength(update);
        }
    }
    // a noble can call a battle on another noble and their army
    // the strengths of the armies are reduced after each battle
    // a noble dies when their army is dead, though battle results may vary
    void battle(Noble& enemy){
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
    void rip(){
        // worst case scenario both die, also avoids division by 0
        resultingStrength(1,1);
        is_alive = false;
    }
private:
    string noble_name;
    vector <Warrior*> army;
    bool is_alive;
};


int main()
{
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
} // main

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
    os << sir.noble_name << " has an army of " << sir.army.size() << endl;
    for (const Warrior* someone : sir.army){
        if (someone){   // exists in vector
            os << *someone << endl;
        }
    }
    return os;
}