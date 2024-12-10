/*
  bounds checking
  jbs
  CS2124
  Inclass Base 
*/

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

void foo() {
    vector<int> v;
    v.push_back(6);

    // What happens heere?
    // v[17] = 42;
    // cout << v[17] << endl;


    v.at(17) = 42;
    cout << v.at(17) << endl;

}

int main() {

    // vector<int> v;
    // v.push_back(6);

    // // What happens heere?
    // // v[17] = 42;
    // // cout << v[17] << endl;


    // v.at(17) = 42;
    // cout << v.at(17) << endl;

    try {
        foo();
    }
    catch (out_of_range ex) {
        cout << "Caught an out_of_range exception\n";
    }
    catch (exception ex) {
        cout << "Caught an exception exception\n";
    }
    // catch (out_of_range ex) {
    //     cout << "Caught an out_of_range exception\n";
    // }

    cout << "Still running\n";
}

