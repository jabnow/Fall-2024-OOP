/*
  abstract.cpp
  24F - Sec C
*/

#include <iostream>
using namespace std;

class Shape { // Abstract class
public:
    Shape(int x, int y) : x(x), y(y) {}
    void move(int deltaX, int deltaY) { x += deltaX;  y += deltaY; }
    virtual void draw() = 0; // Abstract method. Pure virtual
    //void commonDrawingCode() { cout << "Drawing a "; }
private:
    int x, y;
};

void Shape::draw() { cout << "Drawing a "; }

class Triangle : public Shape {
public:
    Triangle(int x, int y) : Shape(x,y) {}
    //void draw() { cout << "Drawing a Triangle\n"; }
    void draw() { 
        //commonDrawingCode();
        Shape::draw();
        cout << "Triangle\n";
    }
};

class Circle : public Shape {
public:
    Circle(int x, int y) : Shape(x,y) {}
    void draw() { cout << "Drawing a Circle\n"; }
};

class Isosceles : public Triangle {
public:
    using Triangle::Triangle;
};

//void foo(Shape aShape) {}

int main() {
    //Shape aShape(3,4);
    Triangle tri(3,4);
    tri.draw();
    Circle circ(10,10);
    circ.draw();

    Isosceles iso(6, 28);
    iso.draw();

}
