#ifndef _GRAPH_
#define _GRAPH_
#include <vector>
#include "BST.h"

using namespace std;

template <typename T>
class Graph{
    public:
        // Specific constructor
        Graph();
        ~Graph();

        void add_vertex(std::vector<T> new_vertex);
        void print();

    private:
        BST<std::vector<T>> *root;
};

#include "Graph.cpp"
#endif