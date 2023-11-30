#include "list.h"
#include <iostream>
#include <stdexcept>
using namespace std; 

List::List(){
    size = 0;
    sentinel_head = new(nothrow) Node();
    sentinel_tail = new(nothrow) Node();
    if(sentinel_head == nullptr || sentinel_tail == nullptr){
        throw runtime_error("Out of Memory");
    }
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
}

List::~List(){
    Node* start = (sentinel_head->next);
    while((start->is_sentinel_node()) == false){
        start = start ->next;
        delete (start->prev);
    }
    delete sentinel_head;
    delete start;
}

// Insert an element at the tail of the linked list 
void List::insert(int v){
    Node* newEnd = new(nothrow) Node(v, sentinel_tail, (sentinel_tail)->prev);
    if(newEnd == nullptr){
        throw runtime_error("Out of Memory");
    }
    (sentinel_tail->prev)->next = newEnd;
    sentinel_tail->prev = newEnd;
    size++;
}

// Delete the tail of the linked list and return the value
// You need to delete the valid tail element, not the sentinel
int List::delete_tail(){
    int ans;
    if(size!=0){
        ans = (sentinel_tail->prev)->get_value();
        Node*a = (sentinel_tail->prev);
        ((sentinel_tail->prev)->prev)->next = sentinel_tail;
        sentinel_tail->prev = sentinel_tail->prev->prev;
        delete a;
        size--;
    }
    return ans;
}

// Return the size of the linked list 
// Do not count the sentinel elements
int List::get_size(){
    return size;
} 

// Return a pointer to the sentinel head of the linked list 
Node* List::get_head(){
    return sentinel_head;
}