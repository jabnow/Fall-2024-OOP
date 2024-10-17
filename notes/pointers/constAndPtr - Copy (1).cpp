/*
  const_ptr.cpp
  
  explore how the keyword const works together with pointers
*/

#include <iostream>
using namespace std;

struct Thing { int val; };


void foo(const Thing& aThing) {
    // 4. What kind of pointer can point to aThing?
    // Thing* p = &aThing;
}


int main()
{
    int x = 17, y = 42;

    // 1. How can we define a pointer that CANNOT modify what it
    //    points at?
    //int* p = &x;
    const int* p = &x;
    //*p = 28;  // how can we prevent that from compiling?

    // 2. how can we define a pointer that CAN ONLY ever point at
    //    one item which it was set to point to initially
    //int* q = &x;
    int* const q = &x;
    //q = &y; // how can we prevent that from compiling?

    // 3. What kind of pointer can point at a constant item?
    const int z = 100;
    //z = 200; // not allowed, of course;
    
    //int* r = &z;
    const int* r = &z;
    //    *r = 300;  // how can we prevent that from compiling?
    
} // main
