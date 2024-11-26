/*
  Vector-generic.cpp
  templated Vector class and printVector function
  24F - Sec A
 */
#include <iostream>
using namespace std;

class Cat{};

template <typename Fred>
class Vector {
public:
    
    //explicit Vector(size_t howMany=0, int val=0)
    explicit Vector(size_t howMany=0, Fred val = Fred())
    {
        theSize = howMany;
        theCapacity = howMany;
        //data = new int[howMany];
        data = new Fred[howMany];
        for (size_t i = 0; i < theSize; ++i) {
            data[i] = val;
        }
    } // Vector(size_t, int)

    // Copy control
    //   Destructor
    ~Vector()
    {
        delete [] data;
    } // ~Vector

    //   Copy Constructor
    Vector(const Vector& rhs)
    {
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new Fred[theCapacity];
        for (size_t i = 0; i < theSize; ++i) {
            data[i] = rhs.data[i];
        }
    } // Vector(Vector)

    //   Assignement Operator
    Vector& operator=(const Vector& rhs)
    {
        if (this != &rhs) {
            // Free up the old (destructor)
            delete [] data;
            // Allocate new
            data = new Fred[rhs.theCapacity];
            // Copy all the stuff
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < theSize; ++i) {
                data[i] = rhs.data[i];
            }
        }
        // Return ourselves
        return *this;
    } // op=


    void push_back(Fred val)
    {
        if (theSize == theCapacity) {
            if (theCapacity == 0) {
                delete [] data;
                data = new Fred[1];
                theCapacity = 1;
            } else {
                Fred* oldData = data;
                theCapacity *= 2;
                data = new Fred[theCapacity];
                for (size_t i = 0; i < theSize; ++i) {
                    data[i] = oldData[i];
                }
                delete [] oldData;
            }
        }
        data[theSize++] = val;
    } // push_back

    size_t size() const { return theSize; }
    void pop_back() { --theSize; }

    void clear() { theSize = 0; };


    // Square brackets?
    const Fred& operator[](size_t index) const {
        return data[index];
    }
    Fred& operator[](size_t index) {
        return data[index];
    }
    
private:
    //int* data;
    Fred* data;
    size_t theSize;
    size_t theCapacity;
}; // class Vector

template <typename Mary>
//void printVector(const Mary& v)
void printVector(const Vector<Mary>& v)
{
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << endl;
} // printVector

int main()
{

    // Not templated.  Our Vector class can only hold ints.
    //Vector v;  
    Vector<int> v;  

    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);
    printVector(v);
    
    v[0] = 100;

    Vector<int> v2 = v;
    //    printVector(v2);

    Vector<int> v3;
    v3 = v;
    //    printVector(v3);

    v3 = Vector<int>(17);
    //    printVector(v2);

    // for (int val : v2) {
    //     cout << val << ' ';
    // }
    // cout << endl;

    vector<Cat> vc;
    // printVector(vc); // Cat has no op<<. Can't print. Won't compile.
    
} // main

