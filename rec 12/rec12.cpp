// Recitation: Doubly linked list
//  Joy Wang 11/22/2024

#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    explicit Node(int val = 0, Node* n = nullptr, Node* p = nullptr) :
            data(val), next(n), prev(p) {}
};

class List {
//    friend ostream& operator<<(ostream& os, const List::Iterator& iter);
    friend ostream& operator<<(ostream& os, const List& list){
        Node* curr = list.header->next;
        while (curr != list.trailer){
            os << curr->data << ' ';
            curr = curr->next;
        }
        return os;
    }
private:
    Node* header;
    Node* trailer;
    size_t curr_size;
public:
    List() : curr_size(0) {  // empty for now
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
    }
    ~List() {
        clear();
        delete header;
        delete trailer;
    }

    void push_back(int data){
        // if empty = header = = before the trailer
        // if not empty = before the trailer
        Node* temp = new Node(data, trailer, (trailer->prev));
        (trailer->prev)->next = temp;
        trailer->prev = temp;
        ++curr_size;
    }

    void pop_back(){
        // is empty or not
        // if not empty, proceed to delete
        if (curr_size != 0){
            Node* temp = trailer->prev;
            // reassign
            (temp->prev)->next = trailer;
            trailer->prev = temp->prev;
            delete temp;
            --curr_size;
        } else {
            return;
        }
    }

    int front() const {
        if (curr_size == 0){
            cerr << "empty" << endl;
//            exit(0);
        }
        return (header->next)->data;
    }
    int& front () {
        if (curr_size == 0){
            cerr << "empty" << endl;
//            exit(0);
        }
        return (header->next)->data;
    }
    int back() const {
        if (curr_size == 0){
            cerr << "empty";
//            exit(0);
        }
        return (trailer->prev)->data;
    }
    int& back() {
        if (curr_size == 0){
            cerr << "empty";
//            exit(0);
        }
        return (trailer->prev)->data;
    }

    size_t size() const { return curr_size; }

    // task 2
    void push_front(int data){
        // if list empty
        // if list not empty
        Node* temp = new Node(data, header->next, header);
        (header->next)->prev = temp;
        header->next = temp;
        ++curr_size;
    }
    void pop_front(){
        // check empty or not
        // if only 1 node, temp->prev is header
        // if > 1 node
        if (curr_size == 0){
            return;
        } else {
            Node* temp = trailer->prev;
            // reassign
            (temp->prev)->next = trailer;
            trailer->prev = temp->prev;
            delete temp;
            --curr_size;
        }
    }

    // task 3
    void clear(){
        while (curr_size > 0){
            pop_back();
        }
    }

    // task 4: index operator (const, non const)
    int operator[](size_t index) const {
        if (index >= curr_size){
            cerr << "out of range";
        }
        Node* curr = header->next;
        for (size_t i=0; i<index;++i){
            curr = curr->next;
        }
        return curr->data;
    }

    int& operator[](size_t index) {
        if (index >= curr_size){
            cerr << "out of range";
        }
        Node* curr = header->next;
        for (size_t i=0; i<index;++i){
            curr = curr->next;
        }
        return curr->data;
    }

    // Task 5: make an iterator class, nested
    class Iterator {
        friend class List;
//        friend ostream& operator<<(ostream& os, const Iterator& iter){
//            os << iter.current << endl;
//            return os;
//        }
        friend bool operator==(const Iterator& lhs, const Iterator& rhs){
            return lhs.current == rhs.current;
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs){
            return lhs.current != rhs.current;
        }
    private:
        Node* current;
    public:
        Iterator(Node* current) : current(current) {}
        Iterator& operator++(){
            current = current->next;
            return *this;
        }
        Iterator& operator--(){
            current = current->prev;
            return *this;
        }
        int& operator*() const {
            return current->data;
        }

    };

    Iterator begin() {
        return Iterator(header->next);
    }

    Iterator end() {
        return Iterator(trailer);
    }

    // it would be good to add a const_iterator class
    // but no time for now

    // task 6: insert method
    Iterator insert(const Iterator& iter, int data) {
        // if at the beginning, call push_front
        // if add the end, call push_back
        // if in the middle...
        Node* temp = iter.current;
        temp->prev = new Node(data, temp, temp->prev);
        (temp->prev)->prev->next = temp->prev;
        ++curr_size;
        return Iterator(temp->prev);
    }

    // task 7: erase method
    Iterator erase(const Iterator& iter){
        if (iter == end()) return iter;
        if (iter == begin()) {
            pop_front();
            return begin();
        }
        Node* prev = iter.current->prev;
        Node* next = iter.current->next;
        delete iter.current;
        // reassign dependencies
        iter.current->prev = prev;
        iter.current->next = next;
        --curr_size;
        return Iterator(iter.current->next);
    }

};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

//// The following should not compile. Check that it does not.
//void changeFrontAndBackConst(const List& theList) {
//    theList.front() = 17;
//    theList.back() = 42;
//}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

//    // Task 8
//    cout << "\n------Task Eight------\n";
//    cout << "Copy control\n";
//    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
//    myList.clear();
//    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
//    printListInfo(myList);
//    cout << "Calling doNothing(myList)\n";
//    doNothing(myList);
//    cout << "Back from doNothing(myList)\n";
//    printListInfo(myList);
//
//    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
//    List listTwo;
//    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
//    printListInfo(listTwo);
//    cout << "listTwo = myList\n";
//    listTwo = myList;
//    cout << "myList: ";
//    printListInfo(myList);
//    cout << "listTwo: ";
//    printListInfo(listTwo);
//    cout << "===================\n";
}
