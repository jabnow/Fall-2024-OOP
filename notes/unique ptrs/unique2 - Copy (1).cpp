/*
  raw_pointers.cpp

  Separate function for each case with Thing(s) on the heap
  - testThing
  - testArrayThing
  - testArrayPtrToThing

  -jbs
 */

#include <iostream>
#include <memory>
using namespace std;

class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs) {
	return os << "Thing: " << rhs.val;
    }
public:
    //Thing(int val=0) : val(val) { cout << "Thing(" << val << ")\n"; }
    Thing(int val = 0) : val(val) { cout << "Initializing Thing(" << val << ")\n"; }
    ~Thing() { cout << "~Thing(): " << val << "\n"; }
    void setVal(int newVal) { val = newVal; }
private:
    int val;
};

void foo() {}

// create / initialize / display / free up a Thing
void testThing(int n)
{
    cout << "starting testThing\n";
    //Thing* pt = new Thing(n);
    //unique_ptr<Thing> pt = unique_ptr<Thing>(new Thing(n));
    unique_ptr<Thing> pt = make_unique<Thing>(n);
    cout << *pt << endl;

    foo();

    // Delete the Thing on the heap
    //delete pt;
} // testThing

// create / fill / display / free up dynamic array of Thing
void testArrayThing(int n)
{
    cout << "starting testArrayThing\n";
    //unique_ptr<Thing[]> pta = unique_ptr<Thing[]>(new Thing[n]);
    unique_ptr<Thing[]> pta = make_unique<Thing[]>(n);

    for (int i = 0; i < n; ++i) {
	//pta[i] = i*i; // implicit conversion
	pta[i].setVal(i*i);
    }

    for (int i = 0; i < n; ++i) {
	cout << pta[i] << ' ';
    }
    cout << endl;
    
    // Delete the dynamic array of Things
    //    delete [] pta;
} // testArrayThing

// create / fill / display / free up dynmaic array of Thing pointers,
// pointing to Things on the heap.
void testArrayPtrToThing(int n) {
    cout << "starting testArrayPtrToThing\n";
    //Thing** ptpa = new Thing*[n];
    //unique_ptr<unique_ptr<Thing>[]> ptpa = unique_ptr<unique_ptr<Thing>[]>(new unique_ptr<Thing>[n]);
    unique_ptr<unique_ptr<Thing>[]> ptpa = make_unique<unique_ptr<Thing>[]>(n);
    for (int i = 0; i < n; ++i) {
	//ptpa[i] = new Thing(i*i);
	//ptpa[i] = unique_ptr<Thing>(new Thing(i*i));
	ptpa[i] = make_unique<Thing>(i*i);
    }
    for (int i = 0; i < n; ++i) {
	cout << *ptpa[i] << ' ';
    }
    cout << endl;
    
    //
    // Clean up!
    //
    // Delete the Things on the heap
    // for (int i = 0; i < n; ++i) {
    //  	delete ptpa[i];
    // }
    // // Delete the dynamic array of Thing pointers
    // delete [] ptpa;
}

int main() {
    testThing(17);
    cout << "back from testThing\n\n";

    testArrayThing(4);
    cout << "back from testArrayThing\n\n";
    
    testArrayPtrToThing(4);
    cout << "back from testArrayPtrToThing\n\n";
}
