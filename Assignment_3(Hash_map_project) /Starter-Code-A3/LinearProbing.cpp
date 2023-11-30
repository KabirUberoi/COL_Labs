#include "LinearProbing.h"
using namespace std;

void Merge(vector<int> &arr, int start, int end){
    int a=start;
    int mid = (start + (end-start)/2);
    int b=mid; 
    int insertat=0;
    int thing[end-start];
    while(a!=(mid) && b!=(end)){
        if(arr[a]<=arr[b]){
            thing[insertat]=arr[a];
            a++; insertat++;
        }
        else{
            thing[insertat]=arr[b];
            b++; insertat++;
        }
    }
    if(a!=mid){
        for(int i=a; i<mid; i++){
            thing[insertat]=arr[a];
            a++; insertat++;
        }
    }
    else if(b!=end){
        for(int i=b; i<end; i++){
            thing[insertat]=arr[b];
            b++; insertat++;
        }
    }
    for(int i=start; i<end; i++){
        arr[i]=thing[i-start];
    }
}

void MergeSort(vector<int> &arr,int start, int end){
    if((end-start)!=1){
        MergeSort(arr,start,(start + (end-start)/2));
        MergeSort(arr,(start + (end-start)/2),end);
        Merge(arr,start,end);
    }
}

LinearProbing::LinearProbing():BaseClass(){
    p[0]=1;
    for(int i=1; i<21; i++){
        p[i]=((p[i-1]*31)%capacity);
    }
    Account Assign = {"a",-1};
    bankStorage1d.resize(capacity);
    for(int i=0; i<bankStorage1d.size(); i++){bankStorage1d[i]=Assign;}
}

int LinearProbing::hash(std::string id) {
    int ans = 0;
    for(int i=0; i<4; i++){
        ans+=((id[i]-65)*p[i]);
        ans = ans%capacity;
    }
    for(int i=4; i<11; i++){
        ans+=((id[i]-48)*p[i]);
        ans = ans%capacity;
    }
    for(int i=12; i<22; i++){
        ans+=((id[i]-48)*p[i-1]);
        ans = ans%capacity;
    }
    return ans; // Placeholder return value
}

void LinearProbing::createAccount(std::string id, int count) {
    Account temp = {id,count};
    int hval = hash(id);
    if(bankStorage1d[hval].balance<0){
        bankStorage1d[hval]=temp;
        KitnaFull++;
    }
    else{
        while(bankStorage1d[hval].balance>=0){
            hval = ((hval+1)%capacity);
        }
        bankStorage1d[hval]=temp;
        KitnaFull++;
    }
}

std::vector<int> LinearProbing::getTopK(int k) {
    vector<int> Sortcheck;
    vector<int> ans;
    for(int i=0; i<capacity; i++){
        if(bankStorage1d[i].balance>=0){
            Sortcheck.push_back(bankStorage1d[i].balance);
        }
    }
    MergeSort(Sortcheck,0,Sortcheck.size());
    if(Sortcheck.size()<=k){
        for(int i=(Sortcheck.size()-1); i>=0; i-- ){
            ans.push_back(Sortcheck[i]);
        }
    }
    else for(int i=(Sortcheck.size()-1); i>=(Sortcheck.size()-k); i--){
        ans.push_back(Sortcheck[i]);
    }
    return ans;
}

int LinearProbing::getBalance(std::string id) {
    int initial = hash(id);
    int hval=((initial + 1)%capacity);
    if(bankStorage1d[initial].id==id){
        return bankStorage1d[initial].balance;;
    }
    else{
        while((bankStorage1d[hval].balance!=-1) && (bankStorage1d[hval].id!=id) && (hval!=initial)){
            hval=((hval + 1)%capacity);
        }
        if(bankStorage1d[hval].id==id){
            return bankStorage1d[hval].balance;
        }
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count) {
    int initial = hash(id);
    int hval=((initial + 1)%capacity);
    if(bankStorage1d[initial].id==id){
        bankStorage1d[initial].balance+=count;
    }
    else{
        while((bankStorage1d[hval].balance!=-1) && (bankStorage1d[hval].id!=id) && (hval!=initial)){
            hval=((hval + 1)%capacity);
        }
        if(bankStorage1d[hval].id==id){
            bankStorage1d[hval].balance+=count;
        }
        else{
            createAccount(id,count);
        }
    }
}

bool LinearProbing::doesExist(std::string id) {
    int initial = hash(id);
    int hval=((initial + 1)%capacity);
    if((bankStorage1d[initial].id)==id){
        return true;
    }
    else{
        while((bankStorage1d[hval].balance!=-1) && (bankStorage1d[hval].id!=id) && (hval!=initial)){
            hval=((hval + 1)%capacity);
        }
        if((bankStorage1d[hval].id)==id){
            return true;
        }
    }
    return false; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    int initial = hash(id);
    int hval=((initial + 1)%capacity);
    if(bankStorage1d[initial].id==id){
        Account assign = {"a",-2};
        bankStorage1d[initial] = assign;
        KitnaFull--;
        return true;
    }
    else{
        while((bankStorage1d[hval].balance!=-1) && (bankStorage1d[hval].id!=id) && (hval!=initial)){
            hval=((hval + 1)%capacity);
        }
        if(bankStorage1d[hval].id==id){
            Account assign = {"a",-2};
            bankStorage1d[hval] = assign;
            KitnaFull--;
            return true;
        }
    }
    return false; // Placeholder return value
}
int LinearProbing::databaseSize() {// IMPLEMENT YOUR CODE HERE
    return KitnaFull; // Placeholder return value
}

