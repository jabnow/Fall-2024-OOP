/*
  oop.cpp
  24F Sec E

  Starting with a struct and a function that is passed an instance of
  that struct.
 */

#include <iostream>
#include <string>
using namespace std;

//struct Person {
class Person {

    friend ostream& operator<<(ostream& os, const Person& rhs);

// private:
//     string name;

public:
    // Person(const string& aName) {
    //     // Will improve later
    //     name = aName;
    // }

    Person(const string& aName) : name(aName) { // initialization list
        //name = aName;
    }

    // Will modify
    //void eating() {
    void eating() const {
        cout << name << " eating\n";
    }

    // Setter / Mutator
    // void setName(const string& aName) {
    //     name = aName;
    // }

    // Getter / Accessor
    //string getName() { // will improve on this
    // const method:
    //string getName() const { // will improve on this
    //string& getName() const { // will improve on this
    const string& getName() const { // will improve on this
        return name;
    }

private:
    string name;


};

void personEating(const Person& aPerson) {
    //cout << aPerson.name << " eating\n";
    cout << aPerson.getName() << " eating\n";
}

//cout << john;
//operator<<(cout, john);
//ostream operator<<(ostream& os, const Person& rhs) {
ostream& operator<<(ostream& os, const Person& rhs) {
    //    os << "Person name: " << rhs.getName();
    os << "Person name: " << rhs.name;
    return os;
}

int main() {
    //Person john;
    Person john("John"); // using a constructor
    //john.name = "John";
    //john.setName("John");
    personEating(john);

    john.eating();

    //Person mary;

    cout << john << endl;
    //operator<<(cout, john);
    //cout.operator<<(john); // NOOO, I don't want to

    vector<Person> people;
    people.push_back(john);
    people.push_back(Person("Fred", 7, 7, 2000));
    people.emplace_back("Mary", 8, 7, 2000);
}
