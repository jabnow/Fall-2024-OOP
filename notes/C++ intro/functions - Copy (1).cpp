/*
  Defining functions and using parameter passing
  24F Sec E
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// void addOne(int someInt) { // pass by value
//     ++someInt;  // Same effect as: someInt += 1;
// }

// function prototype
void addOne(int someInt);

int addOneV2(int someInt) {
    ++someInt;  // Same effect as: someInt += 1;
    return someInt;
}

void addOneRef(int& someInt) { // pass by reference
    ++someInt;  // Same effect as: someInt += 1;
}

//void printVec(vector<int> myVec) { // pass by value
//void printVec(vector<int>& myVec) { // pass by reference
void printVec(const vector<int>& myVec) { // pass by constant reference
    //    cout << myVec << endl;
    for (size_t i = 0; i < myVec.size(); ++i) {
        cout << myVec[i] << ' ';
        //++myVec[i];
    }
    cout << endl;
}

void printVecOfString(const vector<string>& myVec) { // pass by constant reference
    // for (size_t i = 0; i < myVec.size(); ++i) {
    //     cout << myVec[i] << ' ';
    // }
    // cout << endl;

    //    for (string s : myVec) { // by value - inefficient
    //for (string& s : myVec) { // illegal
    for (const string& s : myVec) { 
        cout << s << ' ';
    }
    cout << endl;
    
}

int main() {

    int x = 17;

    addOne(x);
    cout << x << endl;

    x = addOneV2(x);
    cout << x << endl;

    addOneRef(x);
    cout << x << endl;

    vector<int> v {2, 3, 5, 7, 11};
    printVec(v);
    printVec(v);

    vector<string> vs {"Twas", "brillig", "and"};
    printVecOfString(vs);
}

void addOne(int someInt) { // pass by value
    ++someInt;  // Same effect as: someInt += 1;
}

