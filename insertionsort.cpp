//
// Created by KimLAB on 2/15/2019.
//
#include <iostream>

using namespace std;

void InsertionSort(int x[], int n){
    for(int i = 1; i < n; i++){
        int temp = x[i];
        int j = i-1;
        while(j >= 0 && x[j] > temp) {
            x[j + 1] = x[j];
            j--;
        }
        x[j+1] = temp;
    }
}

int main(){
    int arr[] = {6,2,4,1,5,3};
    InsertionSort(arr, 6);
    for (int i = 0; i < 6; i++){
        cout << arr[i] << ", ";
    }
}
