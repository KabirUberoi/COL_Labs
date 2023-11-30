/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    height = 0;
}

SymNode::SymNode(string k){
    height = 0;
    this->key = k;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* a = this->left;
    SymNode* b = this; 

    b->left = a->right;
    a->right = b; 


    b->height = height-2; //Maybe go thru the whole tree and check heights again
    return a; 
}

SymNode* SymNode::RightRightRotation(){
    SymNode* a = this->right;
    SymNode* b = this; 

    b->right = a->left;
    a->left = b; 

    b->height = height-2; //Maybe go thru the whole tree and check heights again
    return a;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* d = this->left->right; 
    SymNode* a = this->left; 
    SymNode* b = this; 
    
    a->right = d->left; 

    b->left = d->right;

    d->left = a;

    d->right = b; 

    a->height--; 
    b->height-=2; 
    d->height++;

    return d; 
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* d = this->right->left; 
    SymNode* a = this->right; 
    SymNode* b = this; 
    
    a->left = d->right; 

    b->right = d->left;

    d->left = b;
    b->par = d; 

    d->right = a; 
    a->par = d;

    a->height-=2; 
    b->height--; 
    d->height++;

    return d; 
}

SymNode::~SymNode(){

}