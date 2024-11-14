// linked-list.cpp
#include <iostream>
using namespace std;

struct Node {
    int data = 0;
    Node* next = nullptr;
};

/*
  display
  length/size
  add, remove at front / back / etc.
  clear
  duplicate
 */

//void listPrint(Node* head) {
void listPrint(const Node* head) {
    while (head) {
        cout << head->data << ' ';
        head = head->next; // bumping
    }
    cout << endl;
}

size_t listLength(const Node* head) {
    size_t length = 0;
    const Node* p = head;
    while (p != nullptr) {
        ++length;
        p = p->next; // bumping
    }
    return length;
}

// const Node* listFindTail(const Node* headPtr) {
//     const Node* last = head;
//     while (last->next != nullptr) {
//         last = last->next; // bumping
//     }
//     return last;
// }

Node* listFindTail(Node* headPtr) {
    if (headPtr == nullptr) {
        return nullptr;
    }
    Node* last = headPtr;
    while (last->next != nullptr) {
        last = last->next; // bumping
    }
    return last;
}

//void listAddTail(Node* headPtr, int data) {
void listAddTail(Node*& headPtr, int data) {
    if (headPtr == nullptr) {
        headPtr = new Node{data};
    } else {
        Node* tail = listFindTail(headPtr);
        tail->next = new Node{data};
    }
}

void listAddHead(Node*& headPtr, int data) {
    // // 1. Create a node for the data
    // Node* p = new Node{data};

    // // 2. Make the new head node point to the old head node
    // p->next = headPtr;

    // Node* p = new Node{data, headPtr};

    // // 3. Make the head pointer point to the new head node
    // headPtr = p;

    headPtr = new Node{data, headPtr};
}

void listRemoveHead(Node*& headPtr) {
    // Don't want to crash on an empty list.
    if (headPtr == nullptr) {
        return;
    }

    // Remember the old head
    Node* oldHead = headPtr;

    // Bump the head pointer
    headPtr = headPtr->next;

    // Free up the old head node
    delete oldHead;
    
}

int main() {
    // Empty list
    Node* myList = nullptr;
    cout << listLength(myList) << endl;
    listAddHead(myList, -1);
    listPrint(myList);

    listAddTail(myList, 6);
    listPrint(myList);
    
    // Add first node to list
    myList = new Node{17};
    
    // Add second node to list
    myList->next = new Node{28};

    // Display the list.
    //    cout << myList->data << ' ' << myList->next->data << endl;

    listPrint(myList);
    cout << listLength(myList) << endl;

    listAddTail(myList, 42);
    listPrint(myList);

    listAddHead(myList, 64);
    listPrint(myList);

}

