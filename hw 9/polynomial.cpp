/*
  polynomial.cpp
  Polynomial class
  Joy Wang
  12/3/2024
 */

#include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;

// definitions below main

int main()
{
        
    //test constructor
    Polynomial p0;                       // 0
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    cout << "displaying polynomials\n"
         << "p0: " << p0 << endl
         << "p1: " << p1 << endl
         << "p2: " << p2 << endl
         << "p3: " << p3 << endl
         << "p4: " << p4 << endl
         << "has_a_zero: " << has_a_zero << endl;

    cout << "p2 + p3: " << (p2+p3) << endl
         << "p2 + p4: " << (p2+p4) << endl
         << "p4 + p2: " << (p4+p2) << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  


    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
        
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;

    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
} // main

// the private struct Node for a single linked list
struct Polynomial::Node {
    int data = 0;
    Node* next = nullptr;
};

// default constructor
Polynomial::Polynomial() : head(new Node{0, nullptr}), power(0) {}

// constructor that takes in a vector
Polynomial::Polynomial(const vector<int>& coeffs) {
    head = nullptr;
    // the power is the size - 1
    power = coeffs.size() - 1;
    // vector is stored greatest term first, as the order passed in
    // reads in the poly to find length and power from end
    // needs to store with the largest value first (reverse)
    for (size_t i=coeffs.size()-1; i > -1; --i){
        add_head(head,coeffs[i]);
    }
    // store in simplified form if there are leading zeroes
    kill_zeroes();
}

// the add_head method used in constructor
void Polynomial::add_head(Node*& h_ptr, int data){
    h_ptr = new Node{data, h_ptr};
}

// gets rid of leading zeroes, eg. {0,0,0,5}
void Polynomial::kill_zeroes() {
    while (head->next && head->data == 0){
        Node* prev = head;
        head = head->next;
        delete prev;
        --power;
    }
}

// destructor
Polynomial::~Polynomial(){
    // reset and clear values
    power = 0;
    while (head) {
        Node* target = head;
        head = head->next;
        delete target;
    }
}

// copy constructor
Polynomial::Polynomial(const Polynomial& other) {
    power = other.power;
    Node* ptr = other.head;
    Node* prior = nullptr;
    // create a new node head
    // link to the copy of the body of the other polynomial
    while(ptr) {
        if (!head){
            head = new Node{ptr->data};
            prior = head;
        } else {
            prior->next = new Node{ptr->data};
            prior = prior->next;
        }
        ptr = ptr->next;
    }
}

// copy assignment constructor
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    // self check
    if (&rhs != this){
        // allocate space
        while (head){
            Node* target = head;
            head = head->next;
            delete target;
        }
        // deep copy
        power = rhs.power;
        Node* ptr = rhs.head;
        Node* prior = nullptr;
        while(ptr) {
            if (!head){
                head = new Node{ptr->data};
                prior = head;
            } else {
                prior->next = new Node{ptr->data};
                prior = prior->next;
            }
            ptr = ptr->next;
        }
    }
   return *this;
}

// += operator
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    size_t curr_pow = power;
    Node* ptr = head;   // const?
    Node* rhs_ptr = rhs.head;   // const?
    // get same length
    while (power < rhs.power) {
        add_head(head, 0);
        ++power;
    }
    while (curr_pow > 0) {
        if (curr_pow > power){
            // this poly is larger
            ptr->data = (ptr->data) + (rhs_ptr->data);
            ptr = ptr->next;
            rhs_ptr = rhs_ptr->next;
        } else {
            // the rhs is larger
            ptr = ptr->next;
        }
    }
}

// + operator function
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial res = lhs;
    res += rhs;
    return res;
}

// == operator
bool Polynomial::operator==(const Polynomial& rhs) const {
    if (power != rhs.power) return false;
    Node* ptr = head;
    Node& rhs_ptr = rhs.head;
    while (ptr){
        if (ptr->data != rhs_ptr->data) return false;
        ptr = ptr->next;
        rhs_ptr = rhs_ptr->next;
    }
    return true;
}

// != operator
bool Polynomial::operator!=(const Polynomial& rhs) const {
    return !(*this == rhs);
}

// evaluate method
/*
 * A method eval that takes a single argument and evaluates the polynomial for that value of "x".
 * So if the variable poly represents the polynomial 4x3 + x + 7, then poly.eval(2) would return 41.
 */
int Polynomial::evaluate(int input) const {
    int res = head->data;
    Node* ptr = head;
    while (ptr->next){
        res = input * res + (ptr->next)->data;
        ptr = ptr->next;
    }
    return res;
}

// output operator <<
/*
 * Use the caret ^ for exponentiation. So: 5x^3 represents five times the term with an exponent of three.
 Do not display terms with zero coefficients. Unless, of course, it is the zero polynomial.
 (If I didn't say that, someone would ask.)
 Do not display coefficients whose value is 1.
 So you would not display 4x^3 + 1x^2, but rather just 4x^3 + x^2.
 (Unless it is the low order coefficient, i.e. the constant term.)
 */
// remember to friend it in the header file
ostream& operator<<(ostream& os, const Polynomial& poly){
    size_t curr_pow = poly.power;
    Polynomial::Node* ptr = poly.head;
    while (ptr->next){
        if (ptr->data == 0){
            continue;
        } else if (ptr->data == 1){
            os << "x";
        } else if (ptr->data == -1){
            os << "-x";
        } else {
            os << ptr->data << "x";
        }
        // now print out the exponent
        if (curr_pow > 1 && ptr->data != 0){
            os << "^" << curr_pow;
        }
        // check sign. Don't want a +(-x)
        if ((ptr->next)->data > 0) {
            os << "+";
        }
        ptr = ptr->next;
        --curr_pow;
    }
    os << ptr->data;
    return os;
}