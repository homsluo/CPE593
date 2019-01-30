/*
	 Author: Yuqing Luo

	 HW1a Eratosthenes
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int n;

    cout << "Please input the n" << '\n';

    cin >> n;
    bool isPrime[n];

    for (int i = 2; i <= n; i++){
        isPrime[i] = true;
    }
    for (int i = 4; i <= n; i += 2){
        isPrime[i] = false;
    }
    for (int i = 3; i <= sqrt(n); i += 2){
        if (isPrime[i]){
            for (int j = i * i; j <= n; j += 2 * i){
                isPrime[j] = false;
            }
        }
    }
    cout << "Prime numbers: ";
    for ( int i = 2; i <= n ; i++){
        if (isPrime[i]){
            cout << i << " ";
        }
    }
    return 0;
}


