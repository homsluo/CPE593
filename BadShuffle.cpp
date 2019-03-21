/*
	 Author: Yuqing Luo

	 Optional: Show distribution of unfair shuffle
*/
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

void BadShuffle(int x[], int n);
void GoodShuffle(int x[], int n);

void BadShuffle(int x[], int n){
    int b[n];
    int count_1 = 0, count_2 = 0, count_3 = 0;
    for (int i = 0; i < 10000; i++) {
        memcpy(b, x, 3*sizeof(int));
        for (int j = 0; j < 3; j++)
            swap(b[j], b[rand() % 3]);
        if(b[0] == 1)
            count_1++;
        else if(b[0] == 2)
            count_2++;
        else
            count_3++;
    }
    cout << "Bad_Count_1: " << count_1 << '\n';
    cout << "Bad_Count_2: " << count_2 << '\n';
    cout << "Bad_Count_3: " << count_3 << '\n';
};

void GoodShuffle(int x[], int n){
    int b[n];
    int count_1 = 0, count_2 = 0, count_3 = 0;
    for (int i = 0; i < 10000; i++) {
        memcpy(b, x, 3*sizeof(int));
        for (int j = 0; j < 3; j++)
            swap(b[j], b[rand() % (3-j)+j]);
        if(b[0] == 1)
            count_1++;
        else if(b[0] == 2)
            count_2++;
        else
            count_3++;
    }
    cout << "Good_Count_1: " << count_1 << '\n';
    cout << "Good_Count_2: " << count_2 << '\n';
    cout << "Good_Count_3: " << count_3 << '\n';
}
int main(){
    int a[] = {1,2,3};
    srand(time(NULL));
    BadShuffle(a, 3);
    cout << '\n';
    GoodShuffle(a, 3);
    return 0;
}