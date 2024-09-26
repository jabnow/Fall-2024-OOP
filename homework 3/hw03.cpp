//
// Created by jwang on 9/23/2024.
// Expanded Warrior class with weapons
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior{
    class Weapon;
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& sword);
    friend ostream& operator<<(ostream& os, const Warrior& some_warrior);
public:
    // make warrior, find warrior may become methods?
    Warrior(const string& name, const string& weapon, int strength) :
    warrior_name(name), weapon_name(weapon, strength) {}
    // setters and getters
    void setStrength(int input) {weapon_name.setStrength(input);}
    int getStrength() const {return weapon_name.getStrength();}
    const string& getName() const {return warrior_name;}
    // battle is now a method
    void battle(Warrior& enemy){
        cout << warrior_name << " battles " << enemy.warrior_name << endl;
        // both are dead
        if (getStrength() == 0 && enemy.getStrength() == 0){
            setStrength(0);
            enemy.setStrength(0);
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (getStrength() == 0 && enemy.getStrength() > 0){
            // only this one is alive, no change
            cout << "He's dead, " << enemy.warrior_name << endl;
        } else if (getStrength() > 0 && enemy.getStrength() == 0){
            // the other is alive, no change
            cout << "He's dead, " << warrior_name << endl;
        } else { // both are alive
            if (getStrength() > enemy.getStrength()){
                // this one is stronger
                setStrength(getStrength() - enemy.getStrength());
                enemy.setStrength(0);
                cout << warrior_name << " defeats " << enemy.warrior_name << endl;
            } else if (getStrength() < enemy.getStrength()){
                // the other is stronger
                enemy.setStrength(enemy.getStrength() - getStrength());
                setStrength(0);
                cout << enemy.warrior_name << " defeats " << warrior_name << endl;
            } else {
                // both are alive and equal
                enemy.setStrength(0);
                setStrength(0);
                cout << "Mutual Annihilation: " << warrior_name << " and " <<
                     enemy.warrior_name << " die at each other's hands" << endl;
            }
        }
    }
private:
    class Weapon{
        friend ostream& operator<<(ostream& os, const Weapon& sword);
    public:
        // actually holds strength, can only be accessed from warrior
        Weapon(const string& weapon_name, int points) : sword_name(weapon_name), strength(points) {}
        // setters and getters
        void setStrength(int points) {strength = points;}
        int getStrength() const {return strength;}
        const string& getName() const {return sword_name;}
    private:
        string sword_name;
        int strength;
    };
    string warrior_name;
    Weapon weapon_name;

};
// overloading nested Weapon operator
ostream& operator<<(ostream& os, const Warrior::Weapon& sword){
    os << "weapon: " << sword.sword_name << ", " << sword.strength; // only one operator?
    return os;
}
// overloading Warrior operator
ostream& operator<<(ostream& os, const Warrior& some_warrior){
    os << "Warrior: " << some_warrior.warrior_name << ", " << some_warrior.weapon_name;
    // but I friended it :(
    return os;
}

// function prototypes
size_t find_warrior(const string& name, const vector<Warrior>& population);
void status(vector<Warrior>& population);
void process_keyword(ifstream& ifs, vector<Warrior>& population);

int main(){
    // try to open file
    ifstream file("warriors.txt");
    if (!file){
        cerr << "cannot open file: warriors.txt";
        exit(1);
    }
    vector<Warrior> population;
    process_keyword(file, population);
    file.close();
    return 0;
}

size_t find_warrior(const string& name, const vector<Warrior>& population){
    for (size_t i = 0; i < population.size(); i++) {
        // check if warrior name is unique, weapons don't matter
        if (population[i].getName() == name) {
            return i;
        }
    }
    return population.size();
}

void status(vector<Warrior>& population){
    cout << "There are: " << population.size() << " warriors\n";
    for (const Warrior& some_warrior : population){
        cout << some_warrior << endl;
    }
}

void process_keyword(ifstream& ifs, vector<Warrior>& population){
    // whether the command is Warrior, Battle, Status
    string keyword, name1, name2, weapon;
    int strength;
    while (ifs >> keyword){
        if (keyword == "Warrior"){
            // construct a Warrior and their Weapon
            ifs >> name1 >> weapon >> strength;
            population.emplace_back(name1, weapon, strength); // why not create temporary object?
        } else if (keyword == "Battle"){
            // call find_and_battle(...)
            ifs >> name1 >> name2;
            size_t w1_place = find_warrior(name1, population);
            size_t w2_place = find_warrior(name2, population);
            // if both exist, then battle and update strengths at location
            if (w1_place != population.size() && w2_place != population.size()){
                population[w1_place].battle(population[w2_place]);
            } else {
                cout << "warriors not found; there was no battle" << endl;
            }
        } else if (keyword == "Status"){
            // call status(...)
            status(population);
        }
    }
}
