/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line
int HEIGHT(SymNode* root){
    if(root == NULL){return -1;}
    int r = HEIGHT(root->right);
    int l = HEIGHT(root->left);
    int ans = (max(l,r)+1);
    root->height = ans;
    return ans;
}

int bf(SymNode* root){
    if(root==NULL){return -1;}
    else{return (HEIGHT(root->left)-HEIGHT(root->right));}
}

void destructor(SymNode* root){
    if(root == NULL){return;}
    destructor(root->left);
    destructor(root->right);
    delete root;
}

SymNode* insertHelper(SymNode* root, string key){
    SymNode* ans = new SymNode(key);
    if(root == NULL){root = ans; return root;}
    else if(key < root->key){
        root->left = insertHelper(root->left, key);
    }
    else if(key > root->key){
        root->right = insertHelper(root->right, key);
    }

    root->height = HEIGHT(root);
    int balance = bf(root);

    if((balance == 2) && (bf(root->left)>=0)){
        root = root->LeftLeftRotation();
    }
    else if((balance == 2) && bf(root->left)==-1){
        root = root->LeftRightRotation();
    }
    else if((balance == -2) && bf(root->right)==1){
        root = root->RightLeftRotation();
    }
    else if((balance == -2) && bf(root->right)<=0){
        root = root->RightRightRotation();
    }
    root->height = HEIGHT(root);
    return root;
}

SymNode* removeHelper(SymNode* root, string key){
    if(root == NULL){return root;}
    else if(root->key < key){
        root->right = removeHelper(root->right,key);
    }
    else if(root->key > key){
        root->left = removeHelper(root->left,key);
    }
    else{
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }
        else if(root->left == NULL || root->right == NULL){
            if(root->left == NULL){
                SymNode* t = root->right; 
                delete root;
                return t;
            }
            else{
                SymNode* t = root->left; 
                delete root;
                return t;
            }
        }
        else{
            SymNode* t = root->right;
            while(t->left!=NULL){t=t->left;}
            root->key = t->key; root->address = t->address;
            root->right = removeHelper(root->right,t->key);
        }
    }
    
    root->height = HEIGHT(root);
    int balance = bf(root);

    if((balance == 2) && (bf(root->left)>=0)){
        root = root->LeftLeftRotation();
    }
    else if((balance == 2) && bf(root->left)==-1){
        root = root->LeftRightRotation();
    }
    else if((balance == -2) && bf(root->right)>=1){
        root = root->RightLeftRotation();
    }
    else if((balance == -2) && bf(root->right)<=0){
        root = root->RightRightRotation();
    }
    root->height = HEIGHT(root);
    return root;
}

SymbolTable::SymbolTable(){
    size = 0; 
    root = NULL; 
}

void SymbolTable::insert(string k){
    int h = HEIGHT(root);
    this->root = insertHelper(this->root,k);
    h = HEIGHT(root);
    this->size++;
}

void SymbolTable::remove(string k){
    int h = HEIGHT(root);
    root = removeHelper(root,k);
    h = HEIGHT(root);
    this->size--;
}

int SymbolTable::search(string k){
    SymNode* temp = root;
    if(temp == NULL){return -2;}
    while(temp!=NULL){
        if(temp->key == k){
            return temp->address;
        }
        else if(temp->key>k){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* temp = root;
    if(temp == NULL){return;}
    while(temp!=NULL){
        if(temp->key == k){
            temp->address = idx;
            return;
        }
        else if(temp->key>k){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return;
}

int SymbolTable::get_size(){
    return size; 
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    destructor(root);
}
