/*
	 Author: Yuqing Luo

	 HW3b QuickSort
*/
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

void quicksort(int x[], int left, int right) {
    if((right - left) <= 0)
        return;
    srand(time(NULL));
    int index = rand() % (right-left+1) + left;
    int pivot = x[index];
    swap(x[index],x[left]);
    int i = left, j = right;

    while(j > i){
        while(x[j] >= pivot && j > i)
            j--;
        while(x[i] <= pivot && j > i)
            i++;
        if(j > i)
            swap(x[i], x[j]);
    }

    swap(x[left], x[i]);
    quicksort(x, left, i-1);
    quicksort(x, i+1, right);
}

int main(){
    ifstream f("hw3.dat");
    if(!f){
        cout << "open failed";
        return 0;
    }

    int n, i = 0;
    f >> n;
    int arr[n] = {0};
    while(!f.eof()){
        f >> arr[i++];
    }

    quicksort(arr, 0, n-1);
    for(int q = 0; q < n; q++){
        cout << arr[q] << " ";
    }
}