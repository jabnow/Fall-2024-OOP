/*
  rec01_start.cpp
  fall 2024
  jwang
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "\nHello World!\n";


    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello World!\n";


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    //cout << x << endl;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << sizeof(x) << sizeof(y) << sizeof(z) << sizeof(pie) << "\n";

    // Task 5  Attempt to assign the wrong type of thing to a variable
    /*
    x = "felix"
    // causes compilation error because of improper instantiation of x.
    */


    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y >= 10 && y <= 20) {
        cout << "10 <= y <= 20\n";
    }
    else {
        cout << "10 > y or y > 20\n";
    }


    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive
    // First with a for loop
    for (int i = 10; i <= 20; i++) {
        cout << i;
    }
    cout << "\n";
    // Then with a while loop
    int j = 10;
    while (j < 21) {
        cout << j;
        ++j;
    }
    cout << "\n";
    // Finally with a do-while loop
    int p = 10;
    do {
        cout << p;
        p++;
    } while (p < 21);
    cout << "\n\n";


    // Task 8  Looping to successfully open a file, asking user for the name
    ifstream ifs;
    string input;

    do{
        cout << "\nInput a file name\n";
        cin >> input;
        ifs.open(input);
    } while (!ifs);

    // Task 9  Looping, reading file word by "word".
    ifstream text("text.txt");
    if (!text) {
        cerr << "Can't open file" << endl;
        return 1;
    }
    string word;
    while (text >> word) {
        cout << word << endl;
    }
    text.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    ifstream numtext("integers.txt");
    int total = 0;
    int value;
    if (!numtext) {
        cerr << "Can't open file" << endl;
    }
    else {
        while (numtext >> value) {
            total += value;
        }
    }
    numtext.close();
    cout << total << endl;

    // Task 11 Open and read a file of integers and words. Display the sum.
    ifstream mixtext("mixed.txt");
    int sums = 0;
    int currnum;
    if (!mixtext)
    {
        cerr << "Can't open file" << endl;
    }
    while (currnum == (int)currnum && mixtext >> currnum) {
        sums += currnum;
    }
    mixtext.close();
    cout << sums << endl;

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> vectorOfEvens;
    for (int i = 10; i < 101; i+=2) {
        vectorOfEvens.push_back(i);
    }
        
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < vectorOfEvens.size(); ++i) {
        cout << vectorOfEvens[i] << endl;
    }
    //         b) using a "ranged for"
    for (int x : vectorOfEvens) {
        cout << x << endl;
    }
    //         c) using indices again but backwards
    size_t start = vectorOfEvens.size();
    for (start; start > 0; start--) {
        cout << vectorOfEvens[start-1] << endl;
    }

    // Task 14. Initialize a vector with the primes less than 20. 
    vector<int> vectorOfPrimes = { 1, 2, 3, 5, 7, 11, 13, 17, 19 };
    for (int x : vectorOfPrimes) {
        cout << x << endl;
    }

    return 0;
} // main

