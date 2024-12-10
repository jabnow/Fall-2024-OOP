/*
  CS2124
  Exceptions and Assertions
  Inclass Base
*/

#include <iostream>
#include <vector>
#include <cstdlib>

#include <exception>
#include <stdexcept>
#include <cassert>

using namespace std;

class MyException : public out_of_range {

};

void bar(int n) {
    if (n > 200) {
        // What to do?
        //throw 3.14159
        //throw exception();
        throw out_of_range("bar: passed a value to large");
    }
}
void foo(int n) { bar(n); }

int main() {
    try {
        foo(300);
    }
    catch (out_of_range ex) {
        cout << "Caught an out_of_range. With the message: " << ex.what() << endl;
    }
}
