#include "stack_a.h"
#include <iostream>
#include <stdexcept>
using namespace std; 

Stack_A::Stack_A(){
    size=0;
}

void Stack_A::push(int data){
    if(size>=1024){
        throw runtime_error("Stack Full");
    }
    else{
        stk[size]=data;
        size++; 
    }
}

int Stack_A::pop(){
    if(size == 0){
        throw runtime_error("Empty Stack");
    }
    else{
        int ans = stk[size-1];
        stk[size-1]=0; size--;
        return ans;
    }
}

int Stack_A::get_element_from_top(int idx){
    if(idx>1023){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[size - 1 - idx];
    }
}

int Stack_A::get_element_from_bottom(int idx){
    if(idx>1023){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[idx];
    }
}

void Stack_A::print_stack(bool top_or_bottom){
    if(top_or_bottom==1){
        for(int i=(size-1);i>=0; i--){
            cout<<stk[i]<<"\n";
        }
    }
    else{
        for(int x:stk){
            cout<<x<<"\n";
        }
    }
}

int Stack_A::add(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int x = this->pop();
        int y = this->pop();
        this->push(x+y);
        return (y+x);
    }
}

int Stack_A::subtract(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int x = this->pop();
        int y = this->pop();
        this->push(y-x);
        return (y-x);
    }
}

int Stack_A::multiply(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int x = this->pop();
        int y = this->pop();
        this->push(x*y);
        return (x*y);
    }
}

int Stack_A::divide(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    if(x == 0){
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

int* Stack_A::get_stack(){
    int* p = stk; 
    return p;
} 

int Stack_A::get_size(){
    return size;
}