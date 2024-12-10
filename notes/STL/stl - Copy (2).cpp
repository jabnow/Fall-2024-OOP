/*
  The STL. Standard Template Library
  24F - Sec A
*/

#include <vector>
#include <iostream> 
#include <list>
#include <algorithm>
using namespace std;

list<char>::iterator myFind(list<char>::iterator start, 
                            list<char>::iterator stop, char target) {
    for (list<char>::iterator iter = start; iter != stop; ++iter) {
        if (*iter == target) return iter;
    }
    return stop;
}

template <typename T, typename U>
T myFind(T start, T stop, U target) {
    for (T iter = start; iter != stop; ++iter) {
        if (*iter == target) return iter;
    }
    return stop;
}

template <typename T, typename U>
T myFind_if(T start, T stop, U pred) {
    for (T iter = start; iter != stop; ++iter) {
        if ( pred(*iter) == true ) return iter;
    }
    return stop;
}

class Elephant{};

// Predicate
bool isEven(int val) { return val % 2 == 0; }

class IsEven {
public:
    // Parenthesis / function call
    bool operator() (int val) { return val % 2 == 0; }
};

class IsMultiple {
public:
    IsMultiple(int div) : divisor(div) {}
    // Parenthesis / function call
    bool operator() (int val) { return val % divisor == 0; }
private:
    int divisor;
};

int main() {

    char foo[] = "Bjarne Stroustrup";
    int len = 17;
    sort(foo, foo+len);
    list<char> lc(foo, foo+len);
    vector<char> vc(lc.begin(), lc.end());

    char* where = find(foo, foo+len, 'j');
    where = find(foo, foo+len, 'Q');
    cout << *where << endl;

    list<char>::iterator where2 = find(lc.begin(), lc.end(), 'j');
    where2 = find(lc.begin(), lc.end(), 'Q');

    myFind(lc.begin(), lc.end(), 'Q');

    //myfind<char*, char>(foo, foo+len, 'Q');  
    myFind(foo, foo+len, 'Q');  
  
    // Elephant dumbo;
    // myFind(foo, foo+len, dumbo);  
  
    vector<int> vi { 1, 3, 5, 9, 4, 12, 13 };
    vector<int>::iterator where3 = find_if(vi.begin(), vi.end(), isEven);
    cout << *where3 << endl;

    //myfind_if(vi.begin(), vi.end(), isEven()); // WRONG!!!


    myFind_if(vi.begin(), vi.end(), isEven);

    // lambda function
    myFind_if(vi.begin(), vi.end(), [] (int val) { return val % 2 == 0; } ) ;

    auto someVar = [] (int val) { return val % 2 == 0; };
    cout << boolalpha << someVar(13) << endl;;
        

    cout << boolalpha << [] (int val) { return val % 2 == 0; } (32) << endl;

    IsEven testIsEven;
    bool result = testIsEven(17);

    //vector<int>::iterator where4 = find_if(vi.begin(), vi.end(), testIsEven ) ;
    auto where4 = find_if(vi.begin(), vi.end(), testIsEven ) ;
    find_if(vi.begin(), vi.end(), IsEven() ) ;

    find_if(vi.begin(), vi.end(), IsMultiple(2) ) ;
    find_if(vi.begin(), vi.end(), IsMultiple(13) ) ;
}

