#include <iostream>

using namespace std;

// Constructors
template <typename T>
BST<T>::BSTNode::BSTNode(T element) : value(element), left(nullptr), right(nullptr) {}

template <typename T>
BST<T>::BST() : root(nullptr) {}

// Destructor
template <typename T>
BST<T>::BSTNode::~BSTNode() {
    if (left) {
        delete left;
    }
    left = nullptr;

    if (right) {
        delete right;
    }
    right = nullptr;
}

template <typename T>
BST<T>::~BST() {
    if (root) {
        delete root;
    }
    root = nullptr;
}

// Insert new node
template <typename T>
void BST<T>::insert(T element) {
    if (!root) {
        root = new BSTNode(element);
    }
    else {
        insert(root, element);
    }
}
template <typename T>
void BST<T>::insert(BST<T>::BSTNode* curr, T element) {
    if (element == curr -> value) {
        return;
    }
    if (element > curr -> value) {
        if (curr -> right == nullptr) {
            curr -> right = new BSTNode(element);
        }
        else {
            insert(curr -> right, element);
        }
    }
    else if (element < curr -> value) {
        if (curr -> left == nullptr) {
            curr -> left = new BSTNode(element);
        }
        else {
            insert(curr -> left, element);
        }
    }
}

// Print tree
template <typename T>
void BST<T>::print() {
    if (!root) {
        cout << "Tree is empty!\n";
    }
    else {
        print(root, 0);
    }
}
template <typename T>
void BST<T>::print(BST<T>::BSTNode* curr, int space) {
    if (!curr) {
        return;
    }
    space += 4;
    print(curr -> right, space);
    cout << endl;
    for (int i = 4; i < space; i++) {
        cout << " ";
    }
    cout << curr -> value << endl;
    print(curr -> left, space);
}

// Get node
template <typename T>
T* BST<T>::get(T element) {
    if (!root) {
        return nullptr;
    }
    if (element == root -> value) {
        T* output = &(root -> value);
        return output;
    }
    else {
        return get(root, element);
    }
}
template <typename T>
T* BST<T>::get(BST<T>::BSTNode* curr, T element) {
    if (element == curr -> value) {
        T* output = &(curr -> value);
        return output;
    }
    else if (element > curr -> value) {
        return get(curr -> right, element);
    }
    else {
        return get(curr -> left, element);
    }
}

// Get value
template <typename T>
T BST<T>::BSTNode::get_value() {
    return value;
}