//
// Created by KimLAB on 2/15/2019.
//
#include<iostream>

using namespace std;

int BinarySearch(int x[], int n, int target){
    int i = 0;
    int j = n-1;
    while(i < j){
        int guess = (i+j)/2;
        if(x[guess] > target)
            j = guess - 1;
        else if(x[guess] < target)
            i = guess + 1;
        else
            return guess;
    }
    return -1;
}

int main(){
    int arr[] = {-6,-2,1,1,2,3,3,4,6,9,11,13,14,15,17,19,22,42,51,55,98};
    int n = sizeof(arr)/sizeof(int);
    int s = BinarySearch(arr, n, -8);
    if(s == -1)
        cout << "err: not exist";
    else
        cout << s;
}
