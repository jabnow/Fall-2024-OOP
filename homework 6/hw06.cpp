/*
  Joy Wang
  bigUnsigned_begin.cpp
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Put your class and all function definitions here.
class BigUnsigned {
    friend ostream& operator << (ostream& os, const BigUnsigned& biggo){
        // zero or empty case
        if (biggo.digits.size()==0 || (biggo.digits.size() == 1
        && biggo.digits[0] == 0)) {
            os << '0';
            return os;
        }
        // undo the reversed digit storage
        for (size_t i = biggo.digits.size(); i > 0; --i) {
            os << biggo.digits[i-1];
        }
        return os;
    }
public:
    // constructor with int or default 0
    BigUnsigned(int num = 0) {
        if (num < 0) {
            // can't have negatives
            digits.push_back(0);
        } else if (num == 0) {
            digits.push_back(0);
        } else {
            // separate each of the digits
            while (num > 0) {
                digits.push_back(num % 10);
                num /= 10;
            }
        }
    }
    // constructor that takes in a string, converts to int digits
    explicit BigUnsigned(const string& number) {
        // Process the string starting from the end
        for (size_t i=0; i < number.length(); i++) {      // OKAY THIS THE PROBLEM
            char val = number[i];
            if (isdigit(val)) {
                int converted = val - '0'; // Convert char to int with ASCII
                digits.push_back(converted);
            } else {
                // don't process non-digits
                break;
            }
        }
        // reverse the order now
        size_t j=digits.size()-1;
        for (size_t i=0; i<digits.size(); i++){
            if (i == j){
                break;
            }
            int temp = digits[i];
            digits[i] = digits[j];
            digits[j] = temp;
            j--;
        }

        // deal with the leading 0s, attempting again...
        // why is that extra 0 everywhere...
        while(digits.size() != 0){
            digits.pop_back();
        }
        if (digits.size() == 0){
            digits.push_back(0);
        }
    }

    // add the + operator, remember to carry over
    BigUnsigned operator+(const BigUnsigned& rhs) const {
        // Store temporary value in result
        BigUnsigned result;
        int carry = 0; // Initialize carry
        // Indexing, i is left and j is right
        size_t i = 0;
        size_t j = 0;
        // If they are not equal length, math ends after the greater number
        // If the remainder is not 0, it needs to be added to the result
        while (i < digits.size() || j < rhs.digits.size() || carry) {
            int left = 0; // Initialize left
            int right = 0; // Initialize right
            // left value
            if (i < digits.size()) { left = digits[i];}
            // right value
            if (j < rhs.digits.size()) { right = rhs.digits[j];}
            // calculate sum
            int curr_sum = left + right + carry;
            result.digits.push_back(curr_sum % 10);
            carry = curr_sum / 10;
            i++;
            j++;
        }
        return result;
    }

    // add the += operator, uses the + operator
    BigUnsigned& operator+=(const BigUnsigned& rhs){
        *this = *this + rhs;
        return *this;
    }

    // add the < operator
    bool operator<(const BigUnsigned& rhs) const {
        // the bigger size is greater
        if (digits.size() != rhs.digits.size()){
            return digits.size() < rhs.digits.size();
        }
        // compare digits starting from biggest
        for (size_t i=digits.size(); i>0; i--){
            if (digits[i-1] != rhs.digits[i-1]){
                return digits[i-1] < rhs.digits[i-1];
            }
            // if the same, check next
        }
        // they are totally the same
        return false;
    }

    // add the == operator
    bool operator == (const BigUnsigned& rhs) const {
        // check the size
        // check the values in digits
        if (digits.size() != rhs.digits.size()) {
            return false;
        }
        for (size_t i=0; i<digits.size(); i++){
            if (digits[i] != rhs.digits[i]){
                return false;
            }
        }
        return true;
    }

    // add the != operator
    bool operator != (const BigUnsigned& rhs) const {
        return !(*this == rhs);
    }

    // for type int
    // Convert int to BigUnsigned for comparison
    friend bool operator==(int num, const BigUnsigned& big) {
        return BigUnsigned(num) == big;
    }

    // Comparison for int vs. BigUnsigned
    friend bool operator!=(int num, const BigUnsigned& big) {
        return !(num == big);
    }

    // add the conditional operator
    explicit operator bool() const { return *this != BigUnsigned(0); }

    // add the <= operator
    bool operator<=(const BigUnsigned& rhs) const {
        return *this < rhs || *this == rhs;
    }

    // add the > operator
    bool operator>(const BigUnsigned& rhs) const {
        return !(*this <= rhs);
    }

    // add the >= operator
    bool operator >= (const BigUnsigned& rhs) const {
        return !(*this < rhs);
    }

    // add the ++i operator
    BigUnsigned& operator++(){
        *this += BigUnsigned(1);
        return *this;
    }

    // add the i++ operator
    BigUnsigned operator++(int){
        BigUnsigned previous = *this;
        ++(*this);
        return previous;
    }


private:
    vector<int> digits;
};

int main()
{
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;
    
    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b 
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    // How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;

} // main

