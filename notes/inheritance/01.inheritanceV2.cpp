
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
    Pet(const string& name) : name(name) {}
    
    //void eat() { cout << "eating" << endl; }
    // Enabling polymorphism
    virtual void eat() { cout << "eating" << endl; }
private:
    string name;
};

class Cat : public Pet {
public:
    //Cat() {}
    //Cat() : Pet() {}
    //Cat(const string& name) : name(name) {}
    //Cat(const string& name) : Pet(name) {}
    //Cat(const string& name, const string& color) : furColor(color), Pet(name) {}

    Cat(const string& name, const string& color) : Pet(name), furColor(color) {}
private:
    string furColor;
};

class Slug : public Pet {
public:
    //Slug(const string& name) : Pet(name) {}
    using Pet::Pet;

    //void eat() { cout << "Slug eating" << endl; }
    void eat() { 
        cout << "Slug ";
        Pet::eat();
    }
};

class Roach : public Pet { };

//void someFunc(Pet aPet) { // Slicing problem
void someFunc(Pet& aPet) { 
    cout << "someFunc: ";
    aPet.eat();  // POLYmorphism?
}


int main() {
    //Pet peeve;
    //Pet peeve(); // Function prototype

    Pet peeve("Peeve");
    peeve.eat();
    someFunc(peeve);

    //Cat felix;
    //Cat felix("Felix"); 
    Cat felix("Felix", "black"); 
    felix.eat();  // code reuse
    someFunc(felix); // Principle of Substitutability: Barbara Liskov

    Slug sluggo("Sluggo");
    sluggo.eat();
    someFunc(sluggo);

    cout << "=============\n";
    /*
    vector<Pet> menagerie;
    menagerie.push_back(peeve);
    menagerie.push_back(felix);
    menagerie.push_back(sluggo);

    for (size_t index = 0; index < menagerie.size(); ++index) {
        menagerie[index].eat();
    }

    cout << "=============\n";

    vector<Pet*> menagerieV2;
    menagerieV2.push_back(&peeve);
    menagerieV2.push_back(&felix);
    menagerieV2.push_back(&sluggo);

    for (size_t index = 0; index < menagerieV2.size(); ++index) {
        menagerieV2[index]->eat();
    }
    */
}
