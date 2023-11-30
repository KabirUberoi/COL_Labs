#include <bits/stdc++.h>
using namespace std;

int main(){
    int a = 5; int b=6; int c = 7; 
    int* A = &a; int*B = &b; 
    A=B; B = &c;
    cout<<*A<<' '<<*B;
}