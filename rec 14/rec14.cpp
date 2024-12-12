/*
  rec14
  Joy Wang
  12 / 11 / 2024
 */

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;


// Node type for the linked list
struct Node {
    Node(int data = 0, Node* next = nullptr): data(data), next(next){}

    int data = 0;
    Node* next = nullptr;
};

// Node type for the ternary tree
struct TNode {
    TNode(int data = 0, TNode* left = nullptr, TNode* mid = nullptr, TNode* right = nullptr) :
    data(data), left(left), mid(mid), right(right) {}

    int data = 0;
    TNode* left = nullptr;
    TNode* mid = nullptr;
    TNode* right = nullptr;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);


//
// Your functions go here
//
//   Task 1 function:
Node* listSum(Node* lst1, Node* lst2){
    // if lists exist
    if (!lst1 && !lst2) return nullptr;
    // if lst 1 > lst 2 (lst 1 longer)
    if (lst1 && !lst2)  return new Node(lst1->data, listSum(lst1->next, nullptr));
    // if lst 2 > lst 1 (lst 2 longer)
    if (!lst1)  return new Node(lst2->data, listSum(nullptr, lst2->next));
    // if both equal length
    return new Node(lst1->data + lst2->data, listSum(lst1->next, lst2->next));
}

//   Task 2 function:
int treeMax(TNode* root){
    int max_val = 0;
    if (!root) throw invalid_argument("the tree does not exist");
    if (root->left) max_val = max(max_val, treeMax(root->left));
    if (root->mid) max_val = max(max_val, treeMax(root->mid));
    if (root->right) max_val = max(max_val, treeMax(root->right));
    return max(max_val, root->data);
}

//   Task 3 function:
bool palindrome(char* word, int len){
    // obvious cases
    if (len < 2) return true;
    if (word[0] != word[len-1]) return false;
    return palindrome(word+1, len-2);
}

//   Task 4 function:
bool parity(int num){
    if (num == 0) return true;  // 0 number of 1s, even
    // if result is false, it flipped odd number of times.
    // if result is even, it flipped even number of times.

    // last bit is 1 so the number itself is odd...
    if (num%2 == 1) return !parity(num / 2);
    else return parity(num / 2);
    // do we want floor division or no?
}


//   Task 5 function: towers of hanoi
int towers(int num, char start, char end, char extra){
    // base case: 1 move left
    // recursive step: move until the biggest disc is at end
    /*
     * each step is 1 disk, n-1 left
     * there are 2 pegs: the extra and end so x2 move
     * then +1 for the last ring per each current iteration
     */
    if (num == 0) return 0;
    int moves = 2 * towers(num-1, start, extra, end) + 1;
    return moves;
}


//   Task 6 verification:
void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}


int main() {
    // We have provided some test code to save you time. Certainly feel
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);
    
    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);


    
    // Task 2:
    cout << "\n==============\n";
    cout << "#2) Testing max of Tree.\n";
     try {
         TNode a{1}, b{2}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
         cout << "treeMax(&f): " << treeMax(&f) << endl;

         // How do you keep this from crashing? try/catch! Here in main!
         cout << treeMax(nullptr) << endl;

     } catch (const invalid_argument& err) {
         cout << "invalid arg error: "  << err.what()<< endl;
     }
    
    // Task 3:
    cout << "\n==============\n"
	 << "#3) Testing palindrome\n";
    cout << boolalpha
	 << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
	 << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
	 << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
	 << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;
    
//     Task 4:
    cout << "\n==============\n"
	 << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }


    
    // Task 5:
    cout << "\n==============\n"
	 << "#5) How many moves are required for various sized towers?\n";
    for (int i = 1; i < 30; ++i) {
	cout << "towers(" << i << ", 'a', 'b', 'c'): "
	     << towers(i, 'a', 'b', 'c') << endl;
    }

    // Task 6:
    cout << "\n==============\n";
    cout << "#6) test the output of this mystery function\n";
    cout << "mystery(0): ";
    mystery(0);
cout << "\nmystery(1): ";
    mystery(1);
cout << "\nmystery(2): ";
    mystery(2);
cout << "\nmystery(3): ";
    mystery(3);
cout << "\nmystery(4): ";
    mystery(4);
cout << "\nmystery(5): ";
    mystery(5);
cout << "\nmystery(6): ";
    mystery(6);
cout << "\nmystery(7): ";
    mystery(7);
cout << "\nmystery(8): ";
    mystery(8);
cout << "\nmystery(9): ";
    mystery(9);
cout << "\nmystery(10): ";
    mystery(10);
}



//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr)
{
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
} // listPrint

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr)
{
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
} // listClear

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals)
{
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
	result = new Node{vals[index-1], result};
    }
    return result;
} // listBuild
