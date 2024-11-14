/*
  Multiple inheritance
  24F - Sec A
*/

// Mulitple inheritance
#include <iostream>
#include <vector>
using namespace std;


class Animal {
public:
    virtual void display() { cout << "Animal\n"; }
};

class Flier {
public:
    // virtual void fly() {
    //     cout << "I'm flying!\n";
    // }
    virtual void fly() = 0;
};

void Flier::fly() {
    cout << "I'm flying!\n";
}



class Cat : public Animal { 
public:
    void purr() { cout << "purrrrr... ";  }
};

class Bat : public Animal, public Flier { 
public:
    void fly() { cout << "Flap...flap ";  }
};

class Insect : public Animal, public Flier {
public:
    void fly() { cout << "Bzzzz. ";  }
};

class Plane : public Flier {
public:
    void fly() { cout << "vrooommmm! ";  }
};

// ==========================================

class  Person {
public:
    Person(const string& name) : name(name) {}
private:
    string name;
};

class Student : public Person {
public:
    Student(const string& name) : Person(name) {}
    virtual void display() const { cout << "Student\n"; }
    double getGPA() const { return 4.0; }
// private:
//     string name;
};

class Instructor : public Person {
public:
    Instructor(const string& name) : Person(name) {}
    virtual void display() const { cout << "Instructor\n"; }
// private:
//     string name;
};

class TA : public Student, public Instructor {
public:
    //TA() : Student(), Instructor() {}
    TA(const string& name) : Student(name), Instructor(name) {}

    void display() const override {
        Student::display();
        Instructor::display();
    }
    //using Student::display;

private:
    //
};

void foo(Instructor& inst) {
    //inst.Student::getGPA();
}

int main() {
    Bat battie;
    battie.display();
    battie.fly();
    Plane sopwithCamel;
    Insect lady;

    
    cout << "==========\n";
    vector<Flier*> vf;
    vf.push_back(&battie);
    vf.push_back(&sopwithCamel);
    vf.push_back(&lady);
    for (Flier* flier : vf) {
        flier->fly();
    }

    //TA rohit;
    TA rohit("Rohit");
    rohit.display();
    //rohit.Student::display();

}



