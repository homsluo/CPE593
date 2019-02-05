//
// Created by LYQ on 2019/2/5.
//
#include <iostream>
using namespace std;

void selectionsort(int x[], int n){
    for(int i = 0; i < n-1; i++){
        int temp = x[i];
        int f = i;
        for(int j = i+1; j < n; j++){
            if(temp > x[j]) {
                temp = x[j];
                f = j;
            }
        }
        x[f] = x[i];
        x[i] = temp;
    }
}

int main(){
    int arr[] = {43,65,4,23,6,98,2,65,7,79};
    selectionsort(arr, sizeof(arr)/ sizeof(arr[0]));
    for(int i = 0; i < sizeof(arr)/ sizeof(arr[0]); i++){
        cout << arr[i] << " ";
    }
}
