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
        double ty = getTime(arr, n, y);
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
        for(int i = left; i < right; i++){
            for(int j = i; j >= 0; j--){
                while(x[j] > x[j+1]){
                    swap(x[j], x[j+1]);
                }
            }
        }

    }

    else{
        int pivot = x[left];
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
    cout << k;

}