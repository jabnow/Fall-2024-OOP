//
// Created by wangj on 11/1/2024.
// inheritance tutorial part 16
//

class Base {
public:
private:
};

class Derived : public Base {
public:
private:
};

int main(){
//    create variables holding instances of
//    each, and a pair of variables that point to each type, i.e. a
//    Base* and a Derived*. Initialize the pointers to null.
    Base base;
    Derived derived;
    Base* baseptr = nullptr;
    Derived* devptr = nullptr;
//    Try assigning your Derived variable to your Base variable.
//    And then try assigning your Base variable to your Derived
//    variable.
    base = derived;
//    derived = base;

//    And now, try assigning the addresses of each of your objects
//    to each of you pointer variables. You know the
//    routine.
// only base classes can point to derived classes;
    baseptr = &base;
    baseptr = &derived;
//    devptr = &base;
    devptr = &derived;
//    devptr = baseptr;
    baseptr = devptr;

//    Can you think of any other things to try? If so, go ahead and do so.
//    1) can ptrs access protected variables / methods directly in base?
//    no, only through child access methods, like private
//    2) how does a destructor deal with inheritance?

}