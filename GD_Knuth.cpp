/*
	 Author: Yuqing Luo

	 optional: find optimal k for Knuth optimized quicksort
*/
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

const double phi = (sqrt(5)-1)/2;
void quicksort(int x[], int left, int right, int GD_k);
double GoldenMeanSearch(double L, double R, double eps, int arr[], int n);
double getTime(int x[], int n, double GD_k);

double getTime(int x[], int n, double GD_k){
    int y[n];
    memcpy(y, x, n* sizeof(int));
    clock_t startTime, endTime;
    startTime = clock();
    quicksort(y, 0, n-1, int(GD_k));
    endTime = clock();
    double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    return time;
}

double GoldenMeanSearch(double L, double R, double eps, int arr[], int n){
    double x, y;
    x = L + (R-L) * (1-phi);
    y = R - (R-L) * (1-phi);
    while(fabs(R-L) > eps){
        double tx = getTime(arr, n, x);
        cout << "K: " << x << ", Time: " << tx << "seconds" << '\n';
        double ty = getTime(arr, n, y);
        cout << "K: " << y << ", Time: " << ty << "seconds" << '\n';
        if (tx > ty){
            L = x;
            x = y;
            y = R - (R-L) * (1-phi);
        }
        else{
            R = y;
            y = x;
            x = L + (R-L) * (1-phi);
        }
    }
    return L;
}

void quicksort(int x[], int left, int right, int GD_k) {
    if((right - left) <= 0)
        return;

    int k = right - left + 1;

    if (k <= GD_k){
        for(int i = 1; i <= right; i++){
            int temp = x[i];
            int j = i-1;
            while(j >= 0 && x[j] > temp){
                x[j+1] = x[j];
                j--;
            }
            x[j+1] = temp;
        }

    }

    else{
        srand(time(NULL));
        int index = rand() % (right-left+1) + left;
        int pivot = x[index];
        swap(x[index], x[left]);
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
    int k = int(GoldenMeanSearch(1, 200, 0.5, arr, n));
    cout << "Best k: " << k << ", Time : " << getTime(arr, n, k);

}

