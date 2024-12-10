/*
  4.Tree
    - How can we use recursion on a binary tree if empty trees are permitted?
    - And how if they are not?
    - consider functions treeSum and treeMax
    - others? treeSumLeaves, treeReverse, ...
  jbs
 */
#include <iostream>   // cout
#include <algorithm>  // max, min
using namespace std;

struct TNode {
    int data;
    TNode* left = nullptr;
    TNode* right = nullptr;
};

int treeSum(const TNode* root) {
    if (root == nullptr) return 0;
    return root->data + treeSum(root->left) + treeSum(root->right);
}

// int treeMin(const TNode* root) {
//     //if (root == nullptr) return 0;
//     if (root == nullptr) return INT_MAX;
//     return min(root->data, min(treeSum(root->left), treeSum(root->right)));
// }


// Do not pass an empty tree
int treeMin(const TNode* root) {
    // leaf
    if (root->left == nullptr && root->right == nullptr) {
        return root->data;
    }
    // Two children
    if (root->left != nullptr && root->right != nullptr) {
        return min(root->data,  min(treeMin(root->left), treeMin(root->right)));
    }
    // Only right child
    if (root->left == nullptr && root->right != nullptr) {
        return min(root->data, treeMin(root->right));
    }
    // Only left child
    //    if (root->left != nullptr && root->right == nullptr) {
    return min(root->data,  treeMin(root->left));
    //    }
    
}


int treeMin2(const TNode* root) {
    int result = root->data;

    if (root->left != nullptr) result = min(result, treeMin2(root->left));
    if (root->right != nullptr) result = min(result, treeMin2(root->right));
    return result;
}

int main() {
    TNode* tree = new TNode{1};
    tree->left = new TNode{2};
    tree->right = new TNode{3};
    tree->left->left = new TNode{4};
    tree->left->right = new TNode{5};

    TNode* tree2 = new TNode{-1};
    tree2->left = new TNode{-2};
    tree2->right = new TNode{-3};
    tree2->left->left = new TNode{-4};
    tree2->left->right = new TNode{-5};

    cout << treeSum(tree) << ' ' << treeSum(tree2) << endl;
    cout << treeMin(tree) << ' ' << treeMin(tree2) << endl;
    cout << treeMin2(tree) << ' ' << treeMin2(tree2) << endl;
}
