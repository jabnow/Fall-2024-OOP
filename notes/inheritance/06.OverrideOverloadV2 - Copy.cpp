/*
  6.OverrideVsOverloadV2.cpp

  Demonstrates that the compiler makes the choice for overloading at
  compile time and overriding at run time.
 */

#include <iostream>
using namespace std;

class Parent {
public:
    virtual void whereami() const { 
        cout << "Parent" << endl; 
    }
};

class Child : public Parent {
public:
    void whereami() const { 
        cout << "Child!!!" << endl; 
    }
};

class Grandchild : public Child {
public:
    void whereami() const { 
        cout << "Grandchild!!!" << endl; 
    }
};

void func(const Parent& base) { cout << "func(Parent)\n"; }
void func(const Child& derived) {cout << "func(Child)\n"; }
  
void otherFunc(Parent& base) {
    func(base);
    base.whereami();
}


int main() {
    Parent parent;
    otherFunc(parent); // obvious, hopefully

    Child child;
    otherFunc(child); // less obvious?

    // Grandchild gc;
    // otherFunc(gc); // ok, by now you know what happens
}
