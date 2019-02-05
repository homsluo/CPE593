//
// Created by LYQ on 2019/2/5.
//
#include <iostream>

using namespace std;

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
void InsertionSort(int x[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = i; j >= 0; j--){
            while(x[j] > x[j+1]){
                swap(x[j], x[j+1]);
            }
        }
    }
}

int main(){
    int arr[] = {43,65,4,23,6,98,2,65,7,79};
    InsertionSort(arr, sizeof(arr)/sizeof(arr[0]));
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        cout << arr[i] << " ";
    }
}
