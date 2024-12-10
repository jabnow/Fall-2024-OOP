// fibonacci
// 24F - Sec A
// - jbs

#include <iostream>
using namespace std;


long long fib(int n) {
    if (n < 2) return n;
    long long last = 0, curr = 1;
    for (int i = 1; i <= n; ++i) {
	long long next = last + curr;
	last = curr;
	curr = next;
    }
    return curr;
}

long long fibR(int n) {
    if (n < 2) return n;
    //return fibR(n-1) + fibR(n-2);
    return (fibR(n-2) + fibR(n-3)) + fibR(n-2);
}


int main() {
    for (int i = 0; i < 10; ++i) {
        cout << "fib(" << i << ") = " << fib(i) << endl;
    }
}
