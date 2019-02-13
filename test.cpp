//
// Created by LYQ on 2019/2/12.
//
#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int a[] = {1,2,3,4,5,6};
    int b[6];
    memcpy(b, a, 6*sizeof(int));
    for(int i = 0; i < 6; i++){
        cout << b[i] << ", ";
    }
}
