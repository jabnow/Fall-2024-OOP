/*
  Vector Class
  Demonstrates:
     Good example of copy control
     Dynamic arrays and pointer arithmetic
     Square bracket operator
     Implementation of an important data structure
  Sec A
 */
#include <iostream>
using namespace std;

class Vector {
public:
    Vector() 
    {
        theSize = 0;
        theCapacity = 0;
        data = nullptr;
    }

    explicit Vector(size_t size, int value = 0) {
        theSize = size;
        theCapacity = size;
        data = new int[theCapacity];
        for (size_t index = 0; index < theSize; ++index) {
            data[index] = value;
        }
    }


    // Copy control
    //
    // Destructor
    ~Vector() 
    {
        delete [] data;
    }

    Vector(const Vector& rhs)
    {
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new int[theCapacity];
        for (size_t index = 0; index < theSize; ++index) {
            data[index] = rhs.data[index];
        }
    }

    Vector& operator=(const Vector& rhs) {
        // self assignment test
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

        // return yourself
        return *this;
    }

    void push_back(int val)
    {
        if (theSize == theCapacity) {
            // What about == 0???
            if (theCapacity == 0) {  // IMPROVED later
                delete [] data;
                theCapacity = 1;
                data = new int[1];  
            } else {
                // Remember the original array
                int* original = data;

                // create a new dynamic array with twice the capacity
                data = new int[2*theCapacity];

                // Copy all of the elements from original array to new one
                for(size_t index = 0; index < theSize; ++index) {
                    data[index] = original[index];
                }

                // free up the old array
                //            delete original; // Wrong
                delete[] original;

                theCapacity *= 2;
            }
        }

        data[theSize] = val;
        ++theSize;
    }

    size_t size() const { return theSize; }
    void pop_back() { --theSize; }
    void clear() { theSize = 0; }

    // Square brackets
    // v[i]
    // v.operator[](i) // Yes
    //int& operator[](size_t index) const { return data[index]; } // NOO
    int operator[](size_t index) const { return data[index]; } // getter
    int& operator[](size_t index) { return data[index]; }
    
    const int* begin() const { return data; }
    const int* end() const { return data + theSize; }
    int* begin()  { return data; }
    int* end()  { return data + theSize; }

private:
    size_t theSize;
    size_t theCapacity;
    int* data;
};

void printVec(const Vector& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
        //v[i] = 100;
    }
    cout << endl;

    for (int val : v) {
    // for (const int* iter = v.begin(); iter != v.end(); ++iter) {
    //     int val = *iter;
        cout << val << ' ';
    }
    cout << endl;
}

int main() {

    Vector v;  // Not templated.  Our Vector class can only hold ints.
    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
        // v[i]
        // operator[](v, i) // No. Stroustrup said no.
        // v.operator[](i) // Yes
    }


    Vector v2(v);
    Vector v3;
    v3 = v;

    v[0] = 100;
    //v.operator[](0) = 100;

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << endl;

    printVec(v);

    //v = 17;
    v = Vector(17);
    printVec(v);

    //    Vector aVec(8, 17);
    Vector aVec(8);
    printVec(aVec);

    //for (int val : aVec) {
    for (int& val : aVec) {
        ++val;
    }
    
    printVec(aVec);

}

