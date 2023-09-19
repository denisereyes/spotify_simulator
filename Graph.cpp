#include <iostream>

using namespace std;

//constructor
template <typename T>
Graph<T>::Graph() {
    root = new BST<vector<T>>();
}

template <typename T>
Graph<T>::~Graph() {
    delete root;
}

template <typename T>
void Graph<T>::add_vertex(std::vector<T> new_vertex) {
    root -> insert(new_vertex);
}

template <typename T>
void Graph<T>::print() {
    root -> print();
}