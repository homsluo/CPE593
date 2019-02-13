/*
	 Author: Yuqing Luo

	 HW3a Insertion sort
*/
#include <iostream>
#include <fstream>

using namespace std;

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
    ifstream f("hw3.dat");
    if(!f){
        cout <<"Open failed!";
        return 1;
    }
    int n, i = 0;
    f >> n;
    int arr[n] = {0};
    while(!f.eof()){
        f >> arr[i++];
    }

    InsertionSort(arr, n);
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}
