//
// Created by wangj on 10/25/2024.
//
#include <iostream>
#include <vector>
#include <string>
#include <cctype> // For isdigit function

using namespace std;

class BigUnsigned {
    friend ostream& operator<<(ostream& os, const BigUnsigned& biggo) {
        if (biggo.digits.empty() || (biggo.digits.size() == 1 && biggo.digits[0] == 0)) {
            os << '0';
            return os;
        }
        // Output the digits in reverse order (from most significant to least)
        for (size_t i = biggo.digits.size(); i > 0; i--) {
            os << biggo.digits[i - 1];
        }
        return os;
    }

public:
    // Constructor with int or default 0
    BigUnsigned(int num = 0) {
        if (num == 0) {
            digits.push_back(0);
        } else {
            while (num > 0) {
                digits.push_back(num % 10);
                num /= 10;
            }
        }
    }

    // Constructor for string input
    explicit BigUnsigned(const string& number) {
        digits.clear(); // Clear previous digits

        // Flag to check if any valid digits are found
        bool valid_digit_found = false;

        // Iterate through each character in the string using a traditional for loop
        for (size_t i = 0; i < number.length(); ++i) {
            char val = number[i]; // Access the character by index
            if (isdigit(val)) {
                int converted = val - '0'; // Convert ASCII character to integer
                digits.push_back(converted); // Store digits in reverse order
                valid_digit_found = true; // Set flag as we found a valid digit
            } else if (valid_digit_found) {
                // If we found a valid digit, break on the first non-digit character
                break;
            }
        }

        // Remove leading zeros: keep popping until the last digit is not zero
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }

        // If no valid digits were found, push back a single zero
        if (!valid_digit_found) {
            digits.push_back(0);
        }
    }

    // Addition operator
    BigUnsigned operator+(const BigUnsigned& rhs) const {
        BigUnsigned result; // Temporary result
        int carry = 0; // Initialize carry

        size_t i = 0; // Index for digits of the first number
        size_t j = 0; // Index for digits of the second number

        // Loop until all digits have been processed
        while (i < digits.size() || j < rhs.digits.size() || carry) {
            int left = (i < digits.size()) ? digits[i] : 0; // Get left digit or 0
            int right = (j < rhs.digits.size()) ? rhs.digits[j] : 0; // Get right digit or 0

            // Calculate current sum
            int curr_sum = left + right + carry;
            result.digits.push_back(curr_sum % 10); // Push current digit to the result
            carry = curr_sum / 10; // Calculate carry for the next iteration

            // Move to the next digits
            i++;
            j++;
        }
        return result; // Return the result
    }

    // Plus-equals operator
    BigUnsigned& operator+=(const BigUnsigned& rhs) {
        *this = *this + rhs; // Use the addition operator
        return *this;
    }

    // Increment operators
    BigUnsigned& operator++() { // Pre-increment
        return *this += BigUnsigned(1);
    }

    BigUnsigned operator++(int) { // Post-increment
        BigUnsigned previous = *this;
        ++(*this);
        return previous;
    }

    // Comparison operators
    bool operator==(const BigUnsigned& rhs) const {
        // Check the size
        if (digits.size() != rhs.digits.size()) {
            return false;
        }
        for (size_t i = 0; i < digits.size(); i++) {
            if (digits[i] != rhs.digits[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const BigUnsigned& rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const BigUnsigned& rhs) const {
        // the bigger size is greater
        if (digits.size() != rhs.digits.size()) {
            return digits.size() < rhs.digits.size();
        }
        // Compare digits starting from the biggest
        for (size_t i = digits.size(); i > 0; i--) {
            if (digits[i - 1] != rhs.digits[i - 1]) {
                return digits[i - 1] < rhs.digits[i - 1];
            }
        }
        // They are totally the same
        return false;
    }

    bool operator<=(const BigUnsigned& rhs) const {
        return *this < rhs || *this == rhs;
    }

    bool operator>(const BigUnsigned& rhs) const {
        return !(*this <= rhs);
    }

    bool operator>=(const BigUnsigned& rhs) const {
        return !(*this < rhs);
    }

    // For type int
    friend bool operator==(int num, const BigUnsigned& big) {
        return BigUnsigned(num) == big; // Convert int to BigUnsigned for comparison
    }

    // Comparison for int vs. BigUnsigned
    friend bool operator!=(int num, const BigUnsigned& big) {
        return !(num == big);
    }

    // Add the conditional operator
    explicit operator bool() const {
        return *this != BigUnsigned(0);
    }

private:
    vector<int> digits; // Store the digits in reverse order
};

int main() {
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

    return 0; // Indicate successful completion
}
