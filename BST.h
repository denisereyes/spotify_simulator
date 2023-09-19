#ifndef BST_H
#define BST_H

class BSTNode;

template <typename T>
class BST {
    public:
        class BSTNode {
            public:
                friend class BST;
                BSTNode(T);
                ~BSTNode();
                T get_value();
            private:
                T value;
                BSTNode* left;
                BSTNode* right;
        };
        BST();
        ~BST();

        void insert(T element);
        T* get(T element);
        void print();

    private:
        BSTNode* root;
        void insert(BSTNode* curr, T element);
        void print(BSTNode* curr, int space);
        T* get(BSTNode* curr, T element);
};

#include "BST.cpp"

#endif