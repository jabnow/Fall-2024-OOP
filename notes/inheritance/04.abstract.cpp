/*
  abstract.cpp
  24F - Sec A
*/

#include <iostream>
using namespace std;

class Shape { // Abstract class
public:
    Shape(int x, int y) : x(x), y(y) {}
    void move(int deltaX, int deltaY) { x += deltaX;  y += deltaY; }
    //virtual void draw() { cout << "Default stuff... "; }
    virtual void draw() = 0; // Pure virtual / Abstract
    //    void commonDrawingCode() { cout << "Drawing a "; }
private:
    int x, y;
};

void Shape::draw() { cout << "Drawing a "; }


class Triangle : public Shape {
public:
    Triangle(int x, int y) : Shape(x,y) {}
    //void draw()  { cout << "Drawing a Triangle"; }
    void draw()  { 
        //cout << "Drawing a Triangle";
        //commonDrawingCode();
        Shape::draw();
        cout << "Triangle\n";
    }
};

class Isosceles : public Triangle {
public:
    using Triangle::Triangle;
};

class Circle : public Shape {
public:
    Circle(int x, int y) : Shape(x,y) {}
    void draw()  { cout << "Drawing a Circle\n"; }
};

int main() {
    // Shape aShape(3,4); // We don't want one
    Triangle tri(3,4);
    tri.draw();
    Circle circ(10,10);
    circ.draw();

    Isosceles iso(7, 12);
    iso.draw();

    iso.Shape::draw();
    cout << endl;
}
