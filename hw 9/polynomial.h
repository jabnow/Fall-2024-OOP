//
// Created by Joy Wang on 12/3/2024.
//

#ifndef AFTER10_POLYNOMIAL_H
#define AFTER10_POLYNOMIAL_H

#include <iostream>
#include <vector>

class Polynomial {  // singly linked list
    struct Node;
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

    void kill_zeroes();
    void add_head(Node*& h_ptr, int data);

private:
    Node* head;
    size_t power;

public:
    Polynomial();
    explicit Polynomial(const std::vector<int>& coeffs);

    ~Polynomial();
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& rhs);

    Polynomial& operator+=(const Polynomial& rhs);
    bool operator==(const Polynomial& rhs) const;
    bool operator!=(const Polynomial& rhs) const;
    int evaluate(int input) const;

};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

void doNothing(Polynomial temp) {}

#endif //AFTER10_POLYNOMIAL_H
