/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

void output_helper(ExprTreeNode* root, SymbolTable* symtable, vector<string> &ans){
    if(root == NULL){return;}
    output_helper(root->right,symtable, ans);
    output_helper(root->left,symtable, ans);
    if(root->type=="VAL"){
        string s = "PUSH "; 
        string s2 = to_string(root->num);
        s = s+s2; 
        ans.push_back(s); 
    }
    else if(root->type=="ADD"){
        ans.push_back(root->type);
    }
    else if(root->type=="SUB"){
        ans.push_back(root->type);
    }
    else if(root->type=="MUL"){
        ans.push_back(root->type);
    }
    else if(root->type=="DIV"){
        ans.push_back(root->type);
    }
    else if(root->type=="VAR"){
        string s = "PUSH mem["; 
        string s2 = to_string(symtable->search(root->id));
        string s3 = "]";
        s = s+s2+s3; 
        ans.push_back(s); 
    }
}

EPPCompiler::EPPCompiler(){
    this->output_file = "targ.txt";
    this->memory_size = 100000;
    for(int i= memory_size-1; i>=0; i--){
        mem_loc.push_back(i);
    }
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    this->output_file = out_file;
    this->memory_size = mem_limit;
    for(int i= memory_size-1; i>=0; i--){
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string> > code){
    vector<string> OutPut;
    for(int i=0; i<code.size(); i++){
        targ.parse(code[i]);
        string Var = "VAR"; string Del = "DEL"; string Ret = "RET"; 
        if((targ.expr_trees[targ.expr_trees.size()-1])->left->type == Var){
            if(targ.symtable->search((targ.expr_trees[targ.expr_trees.size()-1])->left->id)==-1){
                int hashval = mem_loc[mem_loc.size()-1];
                mem_loc.pop_back();
                targ.symtable->assign_address((targ.expr_trees[targ.expr_trees.size()-1])->left->id,hashval);
            }
            output_helper((targ.expr_trees[targ.expr_trees.size()-1])->right, targ.symtable, OutPut);
            string s = "mem["; 
            string s2 = to_string(targ.symtable->search((targ.expr_trees[targ.expr_trees.size()-1])->left->id));
            string s3 = "] = POP";
            s = s+s2+s3; 
            OutPut.push_back(s);
        }
        else if((targ.expr_trees[targ.expr_trees.size()-1])->left->type == Del){
            mem_loc.push_back(targ.last_deleted);
            string s = "DEL = mem["; 
            string s2 = to_string(targ.last_deleted);
            string s3 = "]";
            s = s+s2+s3; 
            OutPut.push_back(s);
        }
        else if((targ.expr_trees[targ.expr_trees.size()-1])->left->type == Ret){
            string s = "RET = POP"; 
            output_helper((targ.expr_trees[targ.expr_trees.size()-1])->right, targ.symtable, OutPut);
            OutPut.push_back(s);
        }
    }
    write_to_file(OutPut);
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> OutPut;
    string Var = "VAR"; string Del = "DEL"; string Ret = "RET"; 
    if((targ.expr_trees[targ.expr_trees.size()-1])->left->type == Var){
        if(targ.symtable->search((targ.expr_trees[targ.expr_trees.size()-1])->left->id)==-1){
            int hashval = mem_loc[mem_loc.size()-1];
            mem_loc.pop_back();
            targ.symtable->assign_address((targ.expr_trees[targ.expr_trees.size()-1])->left->id,hashval);
        }
        output_helper((targ.expr_trees[targ.expr_trees.size()-1])->right, targ.symtable, OutPut);
        string s = "mem["; 
        string s2 = to_string(targ.symtable->search((targ.expr_trees[targ.expr_trees.size()-1])->left->id));
        string s3 = "] = POP";
        s = s+s2+s3; 
        OutPut.push_back(s);
    }
    else if((targ.expr_trees[targ.expr_trees.size()-1])->left->type == Del){
        mem_loc.push_back(targ.last_deleted);
        string s = "DEL = mem["; 
        string s2 = to_string(targ.last_deleted);
        string s3 = "]";
        s = s+s2+s3; 
        OutPut.push_back(s);
    }
    else if((targ.expr_trees[targ.expr_trees.size()-1])->left->type == Ret){
        string s = "RET = POP"; 
        output_helper((targ.expr_trees[targ.expr_trees.size()-1])->right, targ.symtable, OutPut);
        OutPut.push_back(s);
    }
    write_to_file(OutPut);
    return OutPut;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream ans(output_file);
    for(int i=0; i<commands.size(); i++){
        ans<<commands[i]<<"\n"; 
    }
    ans.close();
}

EPPCompiler::~EPPCompiler(){
}