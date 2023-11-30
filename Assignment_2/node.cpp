#include "node.h"
#include <iostream>
#include <stdexcept>
using namespace std; 

// Use to construct a sentinel node (see list.h)
Node::Node(bool sentinel){is_sentinel=sentinel; next = nullptr; prev=nullptr;}  

// Use to construct a regular node
Node::Node(int v, Node* nxt, Node* prv){is_sentinel = false; value = v; next = nxt; prev = prv; }

// Return whether a node is a sentinel node 
// Use it to check if we are at the ends of a list
bool Node::is_sentinel_node(){return is_sentinel;}

// Return the value of a node
int Node::get_value(){return value;}