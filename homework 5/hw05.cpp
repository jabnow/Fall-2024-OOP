//
// Created by Joy Wang on 10/8/2024.
// Dynamic memory with warriors and nobles
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& fighter);
public:
    Warrior(const string& name, double points) :
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
    size_t getArmySize() const {return army.size();}
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
        // find warrior in army
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
                // received comment: Add an extra check using getJob() for fire method to avoid looping through vector unnecessarily
            }
        }
        // if warrior not found in army
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

// function prototypes
// QUESTION: the const declaration... when to use it on the pointer again??
Warrior* find_warrior(const string& name, const vector<Warrior*>& fighters);
Noble* find_noble(const string& name, const vector<Noble*>& noblesse);
//void delete_ptr(vector<Noble*>& noblesse, vector<Warrior*>& fighters);
//void delete_ptr(Noble*& noble, Warrior*& fighter);
void clear_ptrs(vector<Noble*>& noblesse, vector<Warrior*>& fighters);
void display_status(const vector<Noble*>& noblesse,
                    vector<Warrior*> const& fighters);

int main(){
    ifstream input("nobleWarriors.txt");
    if (!input){
        cerr << "unable to open file" << endl;  // should I make this a function???
        exit(1);
    }
    vector<Warrior*> warriors;
    vector<Noble*> nobles;
    string keyword;
    // process the keyword and call correct functions
    while (input >> keyword){
        // create warriors and nobles and fill up the vectors
        string noble, warrior;
        // QUESTION: should I rely on auto int-double conversion,
        // or just declare it double here
        double strength;
        if (keyword == "Noble"){
            input >> noble;
            // check if Noble already exists
            // push_back
            if (find_noble(noble, nobles)){
                cout << "Noble: " << noble << "already exists\n";
            } else {
                nobles.push_back(new Noble(noble));
            }
        } else if (keyword == "Warrior"){
            input >> warrior >> strength;
            // check if Warrior already exists
            // push_back
            if (find_warrior(warrior, warriors)){
                cout << "Warrior: " << warrior << "already exists\n";
            } else {
                warriors.push_back(new Warrior(warrior, strength));
            }

        } else if (keyword == "Hire"){
            input >> noble >> warrior;
            // check if noble exists
            // check if warrior exists
            // check if not already hired (already in the method though?)
            Noble* sir = find_noble(noble, nobles);
            Warrior* knight = find_warrior(warrior, warriors);
            if(sir==nullptr){
                cout << "Noble: " << noble << " not found, cannot hire\n";
            } else if (knight==nullptr){
                cout << "Attempting to hire using unknown warrior: "
                << warrior << endl;
            } else if (sir->getName() == noble && knight->getName()==warrior){
                sir->hire(*knight);
            }

        } else if (keyword == "Fire"){
            input >> noble >> warrior;
            // check if noble is alive / exists
            // check if warrior exists
            // check if not already fired (should be in method?)
            // right noble, right warrior, then delete_ptr
            Noble* sir = find_noble(noble, nobles);
            Warrior* knight = find_warrior(warrior, warriors);
            if(sir==nullptr){
                cout << "Noble: " << noble << " not found, cannot fire\n";
            } else if (knight==nullptr) {
                cout << "Warrior: "<<warrior<<" not found, cannot be fired\n";
            } else if (sir->getName() == noble && knight->getName()==warrior){
                sir->fire(*knight);
//                delete_ptr(sir, knight);    // not necessary
            }

        } else if (keyword == "Battle"){
            string noble2;
            input >> noble >> noble2;
            // find and check if both nobles exist in vector
            Noble* sir = find_noble(noble, nobles);
            Noble* sir2 = find_noble(noble2, nobles);
            if (sir && sir2){
                sir->battle(*sir2);
            } else if (sir==nullptr) {
                cout << "Noble: " << noble << "not found, no battle\n";
            } else {    // else if (sir2==nullptr)
                cout << "Noble: " << noble2 << "not found, no battle\n";
            }

        } else if (keyword == "Status"){
            // display_status
            display_status(nobles, warriors);

        } else if (keyword == "Clear"){
            // clear up the heap
            clear_ptrs(nobles, warriors);
            nobles.clear();
            warriors.clear();
        }
    }
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
    os << sir.noble_name << " has an army of " << sir.army.size() << endl;
    for (const Warrior* someone : sir.army){
        if (someone){   // exists in vector
            os << *someone << endl;
        }
    }
    return os;
}

// all the functions

// search on the heap (Warrior)
// finds the correct Warrior in vector based on name, returns warrior
// if not found, returns nullptr

Warrior* find_warrior(const string& name, const vector<Warrior*>& fighters){
    for(Warrior* warrior : fighters){
        if (warrior->getName() == name){
            return warrior;
        }
    }
    // if warrior not found after all
    return nullptr;
}

// search on the heap (Noble)
// finds the correct Noble in vector based on name, returns warrior
// if not found, returns nullptr
Noble* find_noble(const string& name, const vector<Noble*>& noblesse){
    for (Noble* noble : noblesse){
        if (noble->getName() == name){
            return noble;
        }
    }
    // if noble not found after all
    return nullptr;
}

// delete on the heap (Noble, Warrior) fire
//void delete_ptr(Noble*& noble, Warrior*& fighter){
//    noble->fire(*fighter);
//    fighter->changeJob();
//}

// clear the vectors when clear() is called
// no return type
void clear_ptrs(vector<Noble*>& noblesse, vector<Warrior*>& fighters){
    for (Noble* noble : noblesse){
        delete noble;
    }
    for (Warrior* warrior : fighters){
        delete warrior;
    }
}

// print all the nobles (alive and dead) undifferentiated
// print all the Warriors, employed under nobles or unemployed
// with formatting ====
// no return type
void display_status(const vector<Noble*>& noblesse,
                    const vector<Warrior*>& fighters){
    cout << "Status\n" << "======\n";
    cout << "Nobles:\n";
    // get the current number of warriors (hired) for each noble's army
    if (noblesse.size() == 0){
        cout << "NONE\n";
    } else {
        // these nobles have armies, could be dead or alive
        for (Noble* noble : noblesse){
            cout << *noble;
        }
    }
    cout << "\nUnemployed Warriors:\n";
    // get the unemployed warriors
    size_t unemployed = 0;
    for (const Warrior* const warrior : fighters){
        if (!warrior->getJob()){
            unemployed += 1;
        }
    }
    if (unemployed != 0){
        for (const Warrior* const warrior : fighters){
            if (!warrior->getJob()){ // false
                cout << *warrior << endl;
            }
        }
    } else { // unemployed == 0
        cout << "NONE\n";
    }
}

// process_keywords to make main shorter? yes.
