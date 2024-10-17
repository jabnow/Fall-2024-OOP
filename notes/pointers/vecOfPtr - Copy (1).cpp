// vecOfPtr
// 24F - Sec E
#include <iostream>
#include <vector>
using namespace std;

// printVec: prints the values pointed to by the vector
void printVec(const vector<int*>& v) {
    // First print them using indexed for loop
    for (size_t i = 0; i < v.size(); ++i) {
	cout << *v[i] << ' ';
    }
    cout << endl;

    // Then print them using ranged for loop.
    for (int* p : v) {
	cout << *p << ' ';
    }
    cout << endl;

}

// This DOES compile and modify the elements pointed to. TWICE
void change(const vector<int*>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
 	*v[i] *= 2;
    }

    for (int* p : v) {
	*p *= 2;
    }
}

void change2(const vector<int*>& v) {
    for (const int* p : v) {
        //        *p *= 2;
    }
}

void betterPrintVec(const vector<int*>& v) {
    // Print them using ranged for loop.
    // SAFER. Cannot modify what you are pointing at.
    for (const int* p : v) {
        cout << *p << ' ';
    }
    cout << endl;
}


int main() {

    vector<int*> vip;
    for (int i = 0; i < 10; ++i) {
        vip.push_back(new int(i));
    }
    printVec(vip);

    change(vip);
    printVec(vip);

    change2(vip);
    betterPrintVec(vip);
    
}
