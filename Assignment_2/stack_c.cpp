#include "stack_c.h"
#include <iostream>
#include <stdexcept>
using namespace std; 

// Constructor
Stack_C::Stack_C(){
    stk = new(nothrow) List();
    if(stk == nullptr){
        throw runtime_error("Out of Memory");
    }
}

// Destructor
Stack_C::~Stack_C(){delete stk;}

void Stack_C::push(int data){
    stk->insert(data);
}

int Stack_C::pop(){
    if(stk->get_size()==0){
        throw runtime_error("Empty Stack");
    }
    return (stk->delete_tail());
}

int Stack_C::get_element_from_top(int idx){
    if(idx>(stk->get_size()-1)){
        throw runtime_error("Index out of range");
    }
    else{
        Node* start = (stk->get_head())->next;
        for(int i=0; i<(stk->get_size()-idx-1); i++){
            start = start -> next; 
        }
        return start->get_value();
    }
}

int Stack_C::get_element_from_bottom(int idx){
    if(idx>(stk->get_size()-1)){
        throw runtime_error("Index out of range");
    }
    else{
        Node* start = (stk->get_head())->next;
        for(int i=0; i<idx; i++){
            start = start -> next; 
        }
        return start->get_value();
    }

}

void Stack_C::print_stack(bool top_or_bottom){
    if(top_or_bottom == 0){
        Node* start = (stk->get_head())->next;
        for(int i=0; i<(stk->get_size()); i++){
            cout<<start->get_value()<<"\n";
            start = start -> next; 
        }
    }
    else{
        Node* start = (stk->get_head())->next;
        for(int i=0; i<(stk->get_size()-1); i++){
            start = start -> next; 
        }
        for(int i=0; i<(stk->get_size()); i++){
            cout<<start->get_value()<<"\n";
            start = start -> prev; 
        }
    }
}

int Stack_C::add(){
    if((stk->get_size())<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    this->push(x+y);
    return (x+y);
}

int Stack_C::subtract(){
    if((stk->get_size())<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    this->push(y-x);
    return (y-x);
}

int Stack_C::multiply(){
    if((stk->get_size())<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    this->push(x*y);
    return (x*y);
}

int Stack_C::divide(){
    if((stk->get_size())<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    if(x==0){
        throw runtime_error("Divide by Zero Error");
    }
    int res = (y/x);
    if(x*y<0){
        if(y%x!=0){
            res--;
        }
    }
    this->push(res);
    return(res);
}

List* Stack_C::get_stack(){return stk;} // Get a pointer to the linked list representing the stack

int Stack_C::get_size(){return (stk->get_size());} // Get the size of the 

