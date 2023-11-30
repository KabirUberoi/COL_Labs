/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
//Write your code below this line

void deleteHelper(ExprTreeNode* root){
    if(root == NULL){return;}
    deleteHelper(root->left);
    deleteHelper(root->right);
    delete root;
}

Parser::Parser(){
    symtable = new SymbolTable();
    last_deleted = -1; 
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* eq = new ExprTreeNode();
    eq->type = ":=";

    vector<ExprTreeNode*> Q;

    string del = "del";
    string ret = "ret";
    ExprTreeNode* ans;

    if(expression[0]==del){
        ExprTreeNode* Del = new ExprTreeNode();
        Del->type = "DEL";

        ExprTreeNode* Var = new ExprTreeNode();
        Var->type = "VAR";
        Var->id = expression[2];

        eq->left = Del; 
        eq->right= Var; 
        expr_trees.push_back(eq);
        
        last_deleted = symtable->search(expression[2]);
        symtable->remove(expression[2]);
        return;
    } 
    else if(expression[0]==ret){
        ans = new ExprTreeNode();
        ans->type = "RET";
    }
    else{
        ans = new ExprTreeNode();
        string s = "VAR";
        ans->type = s;
        ans->id = expression[0]; 
        int check = symtable->search(expression[0]);
        if(check == -2){
            symtable->insert(expression[0]);
        }
    }
    for(int i=2; i<expression.size(); i++){
        if(expression[i]=="("){
            continue;
        }
        else if(expression[i]=="+"){
            ExprTreeNode* temp = new ExprTreeNode();
            string s = "ADD"; 
            temp->type = s;
            Q.push_back(temp);
        }
        else if(expression[i]=="-"){
            ExprTreeNode* temp = new ExprTreeNode();
            string s = "SUB"; 
            temp->type = s;
            Q.push_back(temp);
        }
        else if(expression[i]=="*"){
            ExprTreeNode* temp = new ExprTreeNode();
            string s = "MUL"; 
            temp->type = s;
            Q.push_back(temp);
        }
        else if(expression[i]=="/"){
            ExprTreeNode* temp = new ExprTreeNode();
            string s = "DIV"; 
            temp->type = s;
            Q.push_back(temp);
        }
        else if(expression[i]==")"){
            ExprTreeNode* r = Q[Q.size()-1]; Q.pop_back();
            ExprTreeNode* m = Q[Q.size()-1]; Q.pop_back();
            ExprTreeNode* l = Q[Q.size()-1]; Q.pop_back();
            m->right = r; m->left = l; 
            Q.push_back(m);
        }
        else if(expression[i][0]<=57 && expression[i][0]>=48){
            string s = "VAL";
            int value = stoi(expression[i]);
            ExprTreeNode* temp = new ExprTreeNode(); 
            temp->num = value; temp->type = s;
            Q.push_back(temp);
        }
        else{
            ExprTreeNode* temp = new ExprTreeNode();
            string s = "VAR";
            temp->type = s;
            temp->id = expression[i];
            Q.push_back(temp);
        }
    }
    eq->right = Q[0];
    eq->left = ans;
    expr_trees.push_back(eq);
}

Parser::~Parser(){
    for(int i=0; i<expr_trees.size(); i++){
        deleteHelper(expr_trees[i]); 
    }
    delete symtable; 
}