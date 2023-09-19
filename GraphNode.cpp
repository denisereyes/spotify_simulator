#include "GraphNode.h"

using namespace std;

// Constructor
GraphNode::GraphNode(User u) {
    value = u;
    color = "null";
    pred = "null";
    d = 0;
}

// Operator overloading
bool GraphNode::operator==(const GraphNode& other) {
    return (value == other.value);
}
bool GraphNode::operator<(const GraphNode& other) {
    return (value < other.value);
}
bool GraphNode::operator>(const GraphNode& other) {
    return (value > other.value);
}
ostream& operator<<(ostream& os, const GraphNode& se)
{
  os << se.value << ", " << se.d;
  return os;
}

// Setters and Getters
User* GraphNode::get_value() {
    return &value;
}

void GraphNode::set_color(string new_color) {
    color = new_color;
}
string GraphNode::get_color() {
    return color;
}

void GraphNode::set_pred(string new_pred) {
    pred = new_pred;
}
string GraphNode::get_pred() {
    return pred;
}

void GraphNode::set_d(int new_d) {
    d = new_d;
}
int GraphNode::get_d() {
    return d;
}