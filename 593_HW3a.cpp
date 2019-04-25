/*
	 Author: Yuqing Luo

	 HW3a Insertion sort
*/
#include <iostream>
#include <fstream>

using namespace std;

void InsertionSort(int x[], int n){
    for(int i = 1; i < n; i++){
        int temp = x[i];
        int j = i-1;
        while(j >= 0 && x[j] > temp){
            x[j+1] = x[j];
            j--;
        }
        x[j+1] = temp;
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
