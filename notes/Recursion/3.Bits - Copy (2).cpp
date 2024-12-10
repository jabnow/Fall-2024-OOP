/*
  3.Bits
  - What is the recursion involved in splitting a non-negative integer
    "apart" into its digits?
  - What about into its bits?

  24F - Sec A
  - jbs
 */

#include <iostream>
using namespace std;

void printDigits(int n)
{
    if (n < 10) {
        cout << n << ' ';
    } else {
        printDigits(n/10);
        cout << n % 10 << ' ';
    }
} // printDigits

void printDigitsReverse(int n)
{
    if (n < 10) {
        cout << n << ' ';
    } else {
        cout << n % 10 << ' ';
        printDigitsReverse(n/10);
    }
} // printDigitsReverse

void printBits(int n)
{
    if (n < 2) {
        cout << n << ' ';
    } else {
    
        printBits(n / 2);
        cout << n % 2 << ' ';
    }
} // printBits

int countOnes(int n)
{
    //if (n == 0) return 0;
    if (n < 2) return n;
    return countOnes(n/2) + n%2;
} // countOnes

int main()
{
    cout << "printDigits(314159);   ";
    printDigits(314159);
    cout << endl;

    cout << "printDigitsReverse(314159); ";
    printDigitsReverse(314159);
    cout << endl;


    cout << "printBits(5): ";
    printBits(5);
    cout << endl;

    cout << "countOnes(5): " << countOnes(5) << endl;

    cout << "printBits(16): ";
    printBits(16);
    cout << endl;

    cout << "countOnes(16): " << countOnes(16) << endl;    

} // main
