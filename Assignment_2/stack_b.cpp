#include "stack_b.h"
#include <iostream>
#include <stdexcept>
using namespace std; 

Stack_B::Stack_B(){
    stk = new(nothrow) int[1024]();
    if(stk == nullptr){
        throw runtime_error("Out of Memory");
    }
    size = 0;
    capacity = 1024;
    }
Stack_B::~Stack_B(){delete[] stk;}

void Stack_B::push(int data){
    if(size==capacity){
        if(capacity == 1073741824){capacity--; capacity=(capacity*2) +1;}
        else{capacity*=2;}
        int* temp = new(nothrow) int[capacity];
        if(temp == nullptr){
            throw runtime_error("Out of Memory");
        }
        for(int i=0; i<size; i++){
            temp[i]=stk[i];
        }
        delete[] stk;
        stk = temp;
        stk[size]=data;
        size++;
    }
    else{
        stk[size]=data;
        size++;
    }
}

int Stack_B::pop(){
    if(size == 0){
        throw runtime_error("Empty Stack");
    }
    else if((size==((capacity/4)+1))&&(size>1024)){
        int* temp = new(nothrow) int[capacity/2];
        if(temp == nullptr){
            throw runtime_error("Out of Memory");
        }
        for(int i=0; i<(size-1); i++){
            temp[i]=stk[i];
        }
        int ans = stk[size-1];
        delete[] stk;
        stk = temp;
        size--;
        capacity/=2;
        return ans;
    }
    else{
        size--;
        int ans = stk[size];
        stk[size]=0;
        return ans;
    }
}

int Stack_B::get_element_from_top(int idx){
    if(idx>(size-1)){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[size - 1 - idx];
    }
}

int Stack_B::get_element_from_bottom(int idx){
    if(idx>(size-1)){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[idx];
    }
}

void Stack_B::print_stack(bool top_or_bottom){
    if(top_or_bottom==1){
        for(int i=(size-1);i>=0; i--){
            cout<<stk[i]<<"\n";
        }
    }
    else{
        for(int i=0; i<size; i++){
            cout<<stk[i]<<"\n";
        }
    }
}

int Stack_B::add(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    this->push(x+y);
    return (x+y);
}

int Stack_B::subtract(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    this->push(y-x);
    return (y-x);
}

int Stack_B::multiply(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    int x = this->pop();
    int y = this->pop();
    this->push(x*y);
    return (x*y);
}

int Stack_B::divide(){
    if(size<2){
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

int* Stack_B::get_stack(){
    int* p = stk; 
    return p;
} 

int Stack_B::get_size(){
    return size;
}