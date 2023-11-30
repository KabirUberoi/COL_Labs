#include <iostream>
#include <vector>
using namespace std;

class SET{

    public:
        vector<int> v;

        void print(){
            if(v.size()==0){
                cout<<endl;
            }
            else{
                for(int i=0; i<(v.size()-1); i++){
                cout<<v[i]<<',';
                }
                cout<<v[v.size()-1]<<endl;
            }
        }

        int insert(int d){
            if(v.size()==0){
                v.push_back(d);
            }
            else if(d<(v[0])){
                v.insert(v.begin(),d);
            }
            else{
                for(int i=1; i<(v.size()); i++){
                    if((d<v[i])){
                        if(d!=v[i-1]){
                            v.insert(v.begin()+i,d);
                        }
                        break;
                    }
                }
                if(d>v[v.size()-1]){
                    v.push_back(d);
                }
            }
            return v.size();
        }

        int Delete(int d){
            for(int i=0; i<v.size(); i++){
                if(v[i]==d){
                    v.erase(v.begin()+i);
                    break;
                }
            }
            return v.size();
        }

        bool BelongsTo(int d){
            bool ans = 0;
            for(int i=0; i<v.size(); i++){
                if(v[i]==d){
                    ans = 1;
                    break;
                }
            }
            return ans;
        }

        int size(){
            cout<<v.size()<<endl;
            return v.size();
        }

        int Union(SET &b){
            for(int i=0; i<((b.v).size()); i++){
                this->insert((b.v)[i]);
            }
            return v.size();
        }

        int intersection(SET &b){
            vector<int> replace;
            for(int i=0; i<((b.v).size()); i++){
                if(this->BelongsTo((b.v)[i])==1){
                    replace.push_back((b.v)[i]);
                }
            }
            v.clear();
            for(int x: replace){
                v.push_back(x);
            }
            replace.clear();
            return v.size();
        }

        int difference(SET &b){
            if((b.v)==v){
                v.clear();
            }
            else{
                for(int i=0; i<((b.v).size()); i++){
                    if(this->BelongsTo((b.v)[i])==1){
                        this->Delete((b.v)[i]);
                    }
                }
            }
            return v.size();
        }

        int symmetricDifference(SET &b){
            vector<int> replace;
            for(int i=0; i<((b.v).size()); i++){
                if(this->BelongsTo((b.v)[i])==1){
                    replace.push_back((b.v)[i]);
                }
            }
            for(int i=0; i<((b.v).size()); i++){
                this->insert((b.v)[i]);
            }
            for(int x: replace){
                this->Delete(x);
            }
            replace.clear();
            return v.size();
        }
};

vector<SET> M;

int main(){
    int val;
    while(cin>>val){
        if(val == 1){
            int set_num, data; cin>>set_num>>data;
            if((set_num+1)>M.size()){
                for(int i=(M.size()); i<(set_num+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            cout<<M[set_num].insert(data)<<endl;
        }
        else if(val == 2){
            int set_num, data; cin>>set_num>>data;
            if((set_num+1)>M.size()){
                cout<<-1<<endl;
            }
            else{
                cout<<M[set_num].Delete(data)<<endl;
            }
        }
        else if(val == 3){
            int set_num, data; cin>>set_num>>data;
            if((set_num+1)>M.size()){
                cout<<-1<<endl;
            }
            else{
                cout<<M[set_num].BelongsTo(data)<<endl;
            }
        }
        
        else if(val == 4){
            int set_num1, set_num2; cin>>set_num1>>set_num2;
            if((set_num1+1)>M.size()){
                for(int i=(M.size()); i<(set_num1+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            if((set_num2+1)>M.size()){
                for(int i=(M.size()); i<(set_num2+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            cout<<M[set_num1].Union(M[set_num2])<<endl;
        }
        else if(val == 5){
            int set_num1, set_num2; cin>>set_num1>>set_num2;
            if((set_num1+1)>M.size()){
                for(int i=(M.size()); i<(set_num1+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            if((set_num2+1)>M.size()){
                for(int i=(M.size()); i<(set_num2+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            cout<<M[set_num1].intersection(M[set_num2])<<endl;
        }
        else if(val == 6){
            int set_num; cin>>set_num;
            if((set_num+1)>M.size()){
                for(int i=(M.size()); i<(set_num+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            M[set_num].size();
        }
        else if(val == 7){
            int set_num1, set_num2; cin>>set_num1>>set_num2;
            if((set_num1+1)>M.size()){
                for(int i=(M.size()); i<(set_num1+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            if((set_num2+1)>M.size()){
                for(int i=(M.size()); i<(set_num2+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            cout<<M[set_num1].difference(M[set_num2])<<endl;
            
        }
        else if(val == 8){
            int set_num1, set_num2; cin>>set_num1>>set_num2;
            if((set_num1+1)>M.size()){
                for(int i=(M.size()); i<(set_num1+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            if((set_num2+1)>M.size()){
                for(int i=(M.size()); i<(set_num2+1); i++){
                    SET a; 
                    M.push_back(a);
                }
            }
            cout<<M[set_num1].symmetricDifference(M[set_num2])<<endl;
            
        }
        else if(val == 9){
            int set_num; cin>>set_num;
            if((set_num+1)>M.size()){
                cout<<endl;
            }
            else{
                M[set_num].print();
            }
        }
    } 
}