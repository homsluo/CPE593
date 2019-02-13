//
// Created by LYQ on 2019/2/6.
//
#include <iostream>

using namespace std;

void merge(int x[], int left, int right, int result[]);
void mergesort(int x[], int left, int right, int result[]){
    if(right - left == 1){
        if(x[left] > x[right]){
            int temp = x[right];
            x[right] = x[left];
            x[left] = temp;
        }
        return;
    }
    else if(right == left)
        return;
    else{
        mergesort(x, left, (right-left+1)/2-1+left, result);
        mergesort(x, (right-left+1)/2+left, right, result);
        merge(x, left, right, result);
        for(int i = left; i <= right; i++){
            x[i] = result[i];
        }
    }
}

void merge(int x[], int left, int right, int result[]){
    int i = left, j = (right-left+1)/2+left, r = left;
    while(i < (right-left+1)/2+left && j <= right){
        if(x[i] <= x[j])
            result[r++] = x[i++];
        else
            result[r++] = x[j++];
    }
    while(i < (right-left+1)/2+left)
        result[r++] = x[i++];
    while(j <= right)
        result[r++] = x[j++];
}

int main(){
    int arr[] = {9,6,7,22,20,33,16,20,20};
    int n = sizeof(arr)/sizeof(arr[0]);
    int result[n];
    mergesort(arr, 0, n-1, result);

    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}
