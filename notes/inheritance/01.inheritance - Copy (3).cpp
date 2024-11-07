
/*
  1.inheritance.cpp
  Section Base

  Code reuse, principle of substitutability, polymorphism
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pet {
public:
    //void eat() { cout << "eating" << endl; }
    virtual void eat() { cout << "eating" << endl; }
};

class Cat : public Pet {
public:
    void purr() { cout << "purrrrr"; }
};

class Slug : public Pet {
public:
    //void eat() { cout << "Slug eating" << endl; }
    virtual void eat() { 
        cout << "Slug ";
        //eat();
        Pet::eat();
    }
};

class Roach : public Pet { };

//void someFunc(Pet aPet) { // Slicing Problem
void someFunc(Pet& aPet) { // 
    cout << "someFunc: ";
    aPet.eat();
}

void foo(Pet& aPet) {
    //aPet.purr();
}

int main() {
    Pet peeve;
    peeve.eat();
    someFunc(peeve);

    Cat felix;
    felix.eat();            // code reuse
    someFunc(felix);        // Principle of Substitutability - Barbara Liskov

    Slug sluggo;
    sluggo.eat();
    someFunc(sluggo);

    cout << "==============\n";
    vector<Pet> menagerie;
    menagerie.push_back(peeve);
    menagerie.push_back(felix);
    menagerie.push_back(sluggo);
    for (size_t index = 0; index < menagerie.size(); ++index) {
        menagerie[index].eat();
    }

    cout << "==============\n";
    vector<Pet*> menagerieV2;
    menagerieV2.push_back(&peeve);
    menagerieV2.push_back(&felix);
    menagerieV2.push_back(&sluggo);
    for (size_t index = 0; index < menagerieV2.size(); ++index) {
        menagerieV2[index]->eat();
    }

    Pet* petPtr = &felix;
    //petPtr->purr(); // purr is not in the "public interface" of Pet

    foo(peeve);
    foo(felix);
}
