/*
	 Author: Yuqing Luo

	 HW3b QuickSort
*/
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

void GoldenmeanSearch();

void quicksort(int x[], int left, int right, int GD_k) {
    if((right - left) <= 0)
        return;

    int k = right - left + 1;

    if (k <= GD_k){
        for(int i = left; i < right; i++){
            for(int j = i; j >= 0; j--){
                while(x[j] > x[j+1]){
                    swap(x[j], x[j+1]);
                }
            }
        }

    }

    else{
//        srand(time(NULL));
//        int index = rand() % (right-left+1) + left;
        int pivot = x[left];
//        swap(x[index],x[left]);
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
        quicksort(x, left, i-1, GD_k);
        quicksort(x, i+1, right, GD_k);
    }

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

//    GoldenmeanSearch();

    int GD_k = 10;
    int arr_1[n] = {0};

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < n; j++){
            arr_1[j] = arr[j];
        }
        clock_t startTime, endTime;
        startTime = clock();
        quicksort(arr_1, 0, n-1, GD_k);
        endTime = clock();
        double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
//      for(int q = 0; q < n; q++){
//           cout << arr[q] << " ";
//      }
//       cout << endl;
        cout << time << "s" <<endl;
    }
}

