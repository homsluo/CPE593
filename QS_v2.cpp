//
// Created by KimLAB on 2/18/2019.
//
#include <iostream>

using namespace std;

void  QuickSort(int x[], int left, int right){
    if (left >= right)
        return;

    int temp = x[right];
    int i = left, j = right;
    while(i < j){
        while(x[i] <= temp && i < j){
            i++;}
        x[j] = x[i];
        while(x[j] >= temp && i < j){
            j--;}
        x[i] = x[j];
    }
    x[j] = temp;
    QuickSort(x, left, j-1);
    QuickSort(x, j+1, right);
}

int main(){
    int arr[] = {4,1,7,6,9,2,8,0,3,5};
    QuickSort(arr, 0, 9);
    for(int i = 0; i < 10; i++){
        cout << arr[i] << ", ";
    }
}