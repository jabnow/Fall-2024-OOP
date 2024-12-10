// 1.listRecursion
// -jbs
//   - A "few' list functions implemented recursively.
//   - listDup may have been done eariler in the semester, but if not,
//     then definitely do it now.


#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
};
Node* buildList(const vector<int>& vals);

//
// recursive list functions
//


// listPrintIter
void listPrintIter(const Node* hp) {
    const Node* curr = hp;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

// listPrint
void listPrint(const Node* hp) {
    if (hp == nullptr) return;
    cout << hp->data << ' ';

    // Tail recursion
    listPrint( hp->next ); // print the rest of the list

} // listPrint


// listPrintReverse
void listPrintReverse(const Node* hp) {
    if (hp == nullptr) return;

    // NOT Tail recursive
    listPrint( hp->next ); // print the rest of the list
    cout << hp->data << ' ';

} // listPrintReverse


// listDup
Node* listDup(const Node* hp) {
    if (hp == nullptr) return nullptr;

    // Node* smaller = listDup(hp->next); // smaller version of the problem
    // Node* result = new Node{ hp->data, smaller };
    // Combining the previous two lines:
    // Node* smaller = listDup(hp->next); // smaller version of the problem

    // Node* result = new Node{ hp->data, listDup(hp->next) };
    // return result;
    // Combining the previous two lines:
    return new Node{ hp->data, listDup(hp->next) };
} // listDup


// End of recursive list functions


int main() {
    Node* myList = buildList({1, 1, 2, 3, 5, 8, 13, 21, 34, 55});

    //listPrint(myList);
    //listPrintReverse(myList);
    //Node* otherList = listDup(myList);
    //listPrint(myList);
    //listPrint(otherList);
}

Node* buildList(const vector<int>& vals) {
    Node* head = nullptr;
    for (size_t i = vals.size(); i > 0; --i) {
        head = new Node{vals[i-1], head};
    }
    return head;
}
