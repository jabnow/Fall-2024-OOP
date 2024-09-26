//
// Created by Joy Wang on 9/11/2024.
// Warriors battle it out
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Warrior {
    string name;
    int strength;
};

//PARAMETERS GO HERE
void makeWarrior(string& warriorName, int& warriorStrength, vector<Warrior>& allWarriors);
size_t findWarrior(string& warriorName, vector<Warrior>& allWarriors);
void battle(Warrior& warrior1, Warrior& warrior2);
void status(vector<Warrior>& allWarriors);
void processKeywords(ifstream& ifs, vector<Warrior>& allWarriors);

int main(){
    // try to open file
    ifstream ifs("warriors.txt");

    if (!ifs){
        cerr << "unable to open file" << endl;
        return 1;
    }
    // read file, let the warriors fight
    vector<Warrior> warriors;
    processKeywords(ifs, warriors);
    ifs.close();

    return 0;
}

// instantiating a warrior and putting in the vector if unique
void makeWarrior(string& warriorName, int& warriorStrength, vector<Warrior>& allWarriors){
    Warrior newWarrior;
    newWarrior.name = warriorName;
    newWarrior.strength = warriorStrength;
    for (const Warrior& someWarrior: allWarriors){
        if (someWarrior.name == newWarrior.name){
            cerr << "not unique, cannot add" << endl;
        }
    }
    allWarriors.push_back(newWarrior);
}

// called by status, returns the index of one warrior in the vector
size_t findWarrior(string& warriorName, vector<Warrior>& allWarriors){
    // int location;
    for (size_t index = 0; index < allWarriors.size(); index++){
        if (allWarriors[index].name == warriorName){
            return index;
        }
    }
    return allWarriors.size();
}

// two warriors face off and print the result
void battle(const Warrior& warrior1, const Warrior& warrior2){
    cout << warrior1.name << " battles " << warrior2.name << endl;
    if ((warrior1.strength > 0) && (warrior2.strength > 0)){
        // if both are alive
        if (warrior1.strength > warrior2.strength){
            // warrior 1 loses the warrior 2's strength
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
            cout << warrior1.name << " defeats " << warrior2.name << endl;
        } else if (warrior1.strength < warrior2.strength){
            // warrior 2 loses warrior 1's strength
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
            cout << warrior2.name << " defeats " << warrior1.name << endl;
        } else {
            // otherwise, draw and both die
            warrior1.strength = 0;
            warrior2.strength = 0;
            cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name
            << " die at each other's hands" << endl;
        }
    } else if ((warrior1.strength == 0) && (warrior2.strength > 0)){
        // if warrior 1 is already dead
        cout << "He's dead, " << warrior2.name << endl;
    } else if ((warrior2.strength == 0) && (warrior1.strength > 0)){
        // if warrior 2 is already dead
        cout << "He's dead, " << warrior1.name << endl;
    } else {
        // if both are dead
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
}

// prints # of warriors, names, strengths
void status(const vector<Warrior>& allWarriors){
    cout << "There are: " << allWarriors.size() << " warriors" << endl;
    for (const Warrior& someWarrior : allWarriors){
        cout << "Warrior: " << someWarrior.name << ", strength: " << someWarrior.strength << endl;
    }
}

// cleans up main, calls all the other functions
void processKeywords(ifstream& ifs, vector<Warrior>& allWarriors){
    string keyword, name1, name2;
    int strength;
    while (ifs >> keyword){
        if (keyword == "Warrior"){
            // then only one name, one strength
            ifs >> name1 >> strength;
            makeWarrior(name1, strength, allWarriors);
        } else if (keyword == "Status"){
            // then prints out the vector, number of warriors
            status(allWarriors);
        } else if (keyword == "Battle"){
            // then there are two names, strengths
            ifs >> name1 >> name2;
            // find the warriors inside vector
            size_t index1 = findWarrior(name1, allWarriors);
            size_t index2 = findWarrior(name2, allWarriors);
            // if the warriors exist
            if ((index1 != allWarriors.size()) && (index2 != allWarriors.size())){
                battle(allWarriors[index1], allWarriors[index2]);
            } else {
                cerr << "there are no warriors, there was no battle " << endl;
            }
        }
    }
}