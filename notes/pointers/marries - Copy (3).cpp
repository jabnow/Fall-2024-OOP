/*
  marries.cpp
  CS2124
  24F - Sec E
 */

#include <iostream>
#include <string>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs);

public:
    //Person(const string& name) : name(name) {}
    Person(const string& name) : name(name), spouse(nullptr) {}

    // john.marries(mary);
    //void marries(Person betrothed) {
    //void marries(Person& betrothed) {
    bool marries(Person& betrothed) {
        if (spouse == nullptr && betrothed.spouse == nullptr) {
            spouse = &betrothed;
            betrothed.spouse = this;
            return true;
        }
        return false;
    }

private:
    string name;
    //MarriageCertificate mc;
    //string spouse;
    //Person& spouse;
    //Person spouse;
    Person* spouse;  // Association
};

int main()
{
    Person john("John");
    Person mary("Mary");
    cout << john << endl
         << mary << endl;
    john.marries(mary); // failing silently 
    cout << john << endl
         << mary << endl;

    int x = 17;

    // Where is x?
    cout << "x: " << x << "; &x: "  << &x << endl; // address-of operator

    int* p = &x; 
    // int *p = &x; 
    // int * p = &x; 
    cout << "x: " << x << "; &x: "  << &x << "; p: " << p << endl;

    cout << "x: " << x << "; &x: "  << &x
         << "; p: " << p << "; *p: " << *p << endl; // dereference operator
    
    *p = 42;
    cout << "x: " << x << "; &x: "  << &x
         << "; p: " << p << "; *p: " << *p << endl; // dereference operator

    //int* q;
    int* q = nullptr;
    cout << q << endl;
    //cout << *q << endl;

} // main

ostream& operator<<(ostream& os, const Person& rhs)
{
    os << "Name: " << rhs.name;
    // if single ...
    if (rhs.spouse == nullptr) {
        os << "; Single";
    }
    // if married ...
    else {
        //os << "; Married to " << *rhs.spouse; // recursion
        //os << "; Married to " << *rhs.spouse.name; // won't com[ile
        //os << "; Married to " << (*rhs.spouse).name; // Will improve!!!
        os << "; Married to " << rhs.spouse->name; // Thanks Ritchie
    }
    return os;
} // operator<<
