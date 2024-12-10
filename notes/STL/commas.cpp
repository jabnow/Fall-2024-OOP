/*
  commas.cpp
  Yes, there is a comma operator
  But it does not mean the same thing as in Python
 */

#include <utility>
#include <iostream>
#include <string>
using namespace std;

void foo(const vector<int>& vi) {
    for (size_t i = 0, j =0; i < vi.size() && j < vi.size() ; ++i, j += 2) {

    }
}

//void myswap(int x, int y) {
void myswap(int& x, int& y) {
    int tmp = x;
    x = y;
    y = tmp;
}

//int someFunc() {
//pair<int, int> someFunc() {
auto someFunc() { // c++14
    //return 42, 17;
    // pair<int, int> result(42, 17);
    // return result;
    return make_pair(42, 17);
}

int main() {
    int a = 17, b = 42;
    cout << a << ' ' << b << endl;
    //a, b = b, a;
    //a, (b = b), a;

    cout << a << ' ' << b << endl;

    int c = a;
    a = b;
    b = c;

    myswap(a, b);

    //pair<int, int> theResult = someFunc();
    auto theResult = someFunc(); // c++11
    cout << theResult.first << ' ' << theResult.second << endl;

    // c++17
    auto [a, b] = someFunc();
    cout << a << ' ' << b << endl;

    //int x = 17;
    //auto x = 17;
    auto x = 3.14;

    //auto y;
}

