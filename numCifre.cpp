#include <iostream>
using namespace std;

int numCifre(int x){
    if (x<10) return 1;
    else if (x<100) return 2;
    else if (x<1000) return 3;
    else if (x<10000) return 4;
    else if (x<100000) return 5;
    else if (x<1000000) return 6;
    else if (x<10000000) return 7;
    else if (x<100000000) return 8;
    else if (x<1000000000) return 9;
}
/*
int main (){
    int c; cin>>c;
    cout<< numCifre (c);
    return 0;
}*/
