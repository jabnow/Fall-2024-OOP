/*
  oop2.cpp
  CS2124
  24F - Sec E
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs);
public:
    // Nesting publicly
    class Date {
        friend ostream& operator<<(ostream& os, const Date& rhs);
    public:
        Date(int m, int d, int y) : month(m), day(d), year(y) {}
    private:
        int month, day, year;
    };

    //Person(const string& name) : name(name) { }
    Person(const string& name, int month, int day, int year)
         //: name(name), bday(Date(month, day, year)) { }
        : name(name), bday(month, day, year) { }
private:    
    string name;
    Date bday;
};

int main() {
    Person john("John", 4, 20, 2005);
    cout << john << endl;

    //Date independenceDay(7, 4, 1776);
    Person::Date independenceDay(7, 4, 1776);
    cout << independenceDay << endl;
}

ostream& operator<<(ostream& os, const Person& rhs) {
    os << "Person: " << rhs.name; //  << ", dob: " << rhs.bday;
    return os;
}

//ostream& operator<<(ostream& os, const Date& rhs) {
ostream& operator<<(ostream& os, const Person::Date& rhs) {
    os << rhs.month << '/' << rhs.day << '/' << rhs.year;
    return os;
}

