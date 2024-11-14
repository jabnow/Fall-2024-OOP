/*
  08.polyConst
  24F - Sec A
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() { this->foo(); }
    void display() { this->foo(); }

    virtual void foo() const { cout << "Base\n"; }
};

class Derived : public Base {
public:
    Derived(int n) : Base(), x(n) {}
    //Derived(int n) : x(n), Base() {}
    void foo() const override { cout << "Derived: x == " << x << endl; }
private:
    int x;
};

int main() {
    Derived der(17);
    der.display();
}
