//
// Created by KimLAB on 2/18/2019.
//
#include <iostream>
using namespace std;
void InsertionSort(int x[], int n){
    for (int i = 1; i < n; i++){
        int temp = x[i];
        int j = i-1;
        while(j >= 0 && x[j] > temp){
            x[j+1] = x[j];
            j--;
        }
        x[j+1] = temp;
    }
}
int BinarySearch(int x[], int left, int right, int target){
    if(right <= left)
        return -1;
    int guess = (left+right)/2;
    if(x[guess] > target)
        return BinarySearch(x, left, guess, target);
    else if(x[guess] < target)
        return BinarySearch(x, guess, right, target);
    else
        return guess;
}

int main(){
    int a[] = {1,2,3,4,5,6,7,8,9,8,6,3,1,-1,-2,-3,-4};
    int n = sizeof(a)/sizeof(int);
    InsertionSort(a, n);
    int s = BinarySearch(a, 0, n-1, -1);
    cout << s;
}
