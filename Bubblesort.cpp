//
// Created by LYQ on 2019/2/1.
//
#include <iostream>

using namespace std;

void bubbleSort(int x[], int n){
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1;j++ ){
            if(x[j] > x[j+1]){
                int temp = x[j+1];
                x[j+1] = x[j];
                x[j] = temp;
            }

        }
    }
}

int main(){
    int arr[] = {3,2,1};
    bubbleSort(arr, 3);
    for(int i = 0; i < 3; i++){
        cout << arr[i];
    }
}
