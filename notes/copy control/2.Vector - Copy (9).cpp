/*
  Vector Class
  Demonstrates:
     Good example of copy control
     Dynamic arrays and pointer arithmetic
     Square bracket operator
     Implementation of an important data structure
  Sec E - 24F
 */
#include <iostream>
using namespace std;

class Vector {
public:
    Vector() {
        theSize = 0;
        // theCapacity = 8;
        // data = new int[theCapacity];
        theCapacity = 0;
        data = nullptr;
    }

    // Vector v(8, 17);
    
    explicit Vector(size_t size, int value = 0) {
        theSize = size;
        theCapacity = size;
        data = new int[theCapacity];
        for (size_t index = 0; index < theSize; ++index) {
            data[index] = value;
        }
    }

    //
    // Copy control
    //
    // Destructor
    ~Vector() {
        //delete data; // Nooo
        delete [] data;
    }
    // Copy Constructor
    Vector(const Vector& rhs) {
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new int[theCapacity];
        for (size_t index = 0; index < theSize; ++index) {
            data[index] = rhs.data[index];
        }
    }

    Vector& operator=(const Vector& rhs) {
        // Self-assignment check
        if (this != &rhs) {
            // free up
            delete [] data;

            // allocate and copy
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            data = new int[theCapacity];
            for (size_t index = 0; index < theSize; ++index) {
                data[index] = rhs.data[index];
            }
        }
        // return ourself
        return *this;
    }

    void push_back(int val) {
        if (theSize == theCapacity) {
            if (theCapacity == 0) { // update later
                delete [] data;
                theCapacity = 1;
                data = new int[1];
            }
            
            // Remember the old
            int* old = data;

            // double the capacity -- allocate a new array
            data = new int[theCapacity * 2];

            // copy from old to new
            for (size_t index = 0; index < theSize; ++index) {
                //data.push_back // NOOOO!!!!

                data[index] = old[index];
            }
            
            delete [] old;
            theCapacity *= 2;
        }

        data[theSize] = val;
        ++theSize;
    }

    size_t size() const { return theSize; }

    void pop_back() { --theSize;  }

    void clear() { theSize = 0; }

    // Square brackets
    // v[i]
    // v.operator[](i)
    //int& operator[] (size_t index) const  { return data[index]; }
    int operator[] (size_t index) const  { return data[index]; }
    int& operator[] (size_t index) { return data[index]; }
    
    const int* begin() const { return data; }
    const int* end() const { return data + theSize; }

    int* begin() { return data; }
    int* end() { return data + theSize; }

private:
    size_t theSize;
    size_t theCapacity;
    int* data;
};

void printVec(const Vector& v) {
    // for (size_t i = 0; i < v.size(); ++i) {
    //     cout << v[i] << ' ';
    //     //v[i] = 17;
    // }
    // cout << endl;

    for (int val : v) {
    // for (int* iter = v.begin(); iter != v.end(); ++iter) {
    //     int val = *iter;
        cout << val << ' ';
    }
    cout << endl;

    // for (int& val : v) {
    //  // for (int* iter = v.begin(); iter != v.end(); ++iter) {
    //  //     int& val = *iter;
    //     ++val;
    // }

}

int main() {

    Vector v;  // Not templated.  Our Vector class can only hold ints.
    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
        // v[i]
        // v.operator[](i)
        
    }
    cout << endl;

    printVec(v);
    
    Vector v2(v);
    printVec(v2);
    Vector v3 = v;
    printVec(v3);
    Vector v4;
    printVec(v4);
    v4 = v;
    //v4.operator=(x)
    printVec(v4);

    v[0] = 100;
    //v.operator[](0) = 100;
    printVec(v);
    printVec(v);
    
    //v = 17;
    v = Vector(17);

    printVec(v);

    Vector v5(6, 28);
    printVec(v5);

    Vector v6(6);
    printVec(v6);

    for (int& val : v6) {
        ++val;
    }
    printVec(v6);
}

