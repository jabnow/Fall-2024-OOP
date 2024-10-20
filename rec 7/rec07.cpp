/*
  rec07_begin.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational{
    friend istream& operator>>(istream& is, Rational& rhs){
        char filler;
        is >> rhs.numerator >> filler >> rhs.denominator;
        rhs.normalize();
        return is;
    }
    friend ostream& operator<<(ostream& os, const Rational& rhs){
        os << rhs.numerator << "/" << rhs.denominator;
        return os;
    }
    // friends
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
private:
    int numerator;
    int denominator;
public:
    Rational(int numerator=0, int denominator=1){
        this->numerator = numerator;
        this->denominator = denominator;
        normalize();
    }

    // bool operator
    explicit operator bool() const {return numerator != 0;} // why numerator tho

    // can normalize be a method?
    void normalize(){
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        // special cases: gcd, also denominator, cannot be negative
        if (denominator < 0){
            numerator *= -1;
            numerator *= -1;
        }
    }

    // += as a method, called by + operator
    Rational& operator+=(const Rational& rhs){
        if (denominator == rhs.denominator){
            numerator += rhs.numerator;
        } else {
            numerator = numerator*rhs.denominator + rhs.numerator*denominator;
            denominator *= rhs.denominator;
        }
        normalize();
        return *this;
    }

    // pre increment ++i, as member and friend
    Rational& operator++(){
        numerator += denominator;
        return *this;
    }
// post increment i++, as member and friend
// don't return by reference because local scope
    Rational operator++(int){
        Rational prev(*this);
        numerator += denominator;
        return prev;
    }

};
// == operator
bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator == rhs.numerator &&
    lhs.denominator == rhs.denominator);
//    return !(lhs < rhs || rhs < lhs);
}
// < operator friend
bool operator<(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator * rhs.denominator)<(rhs.numerator * lhs.denominator);
}

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
Rational operator--(Rational& rhs, int);
Rational& operator--(Rational& rhs);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members and not friends should have
// their definitions here...

// + operator that calls
Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result(lhs);
    // if denominators equal, just add numerators
    result += rhs;
    return result;
}

// != operator
bool operator!=(const Rational& lhs, const Rational& rhs){
    return (lhs < rhs) || (rhs < lhs);
}
// <= operator
bool operator<=(const Rational& lhs, const Rational& rhs){
    return !(rhs < lhs);
}
// >= operator
bool operator>=(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs);
}

// > operator
bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs) && !(lhs == rhs);
}

// pre decrement --i, as non-member and friend
Rational& operator--(Rational& rhs){
    rhs += -1;
    return rhs;
}
// post-decrement i--, as non-member and friend
// don't return by reference because local scope
Rational operator--(Rational& rhs, int){
    Rational prev(rhs);
    rhs += -1;
    return prev;
}