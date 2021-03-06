/*
	 Author: Yuqing Luo

	 HW1a Eratosthenes
*/

#include <iostream>

using namespace std;

uint64_t choose(int n, int r){
    if ((n < r) || (n > 500)) {
        cout << "error input" << '\n';
        return 0;
    };
    if ((n == r) || (r == 0))
        return 1;
    static uint64_t memo[500][500] = {0};
    if (memo[n][r] != 0)
        return memo[n][r];
    return memo[n][r] = choose (n - 1, r - 1) + choose (n - 1, r);
};

int main(){
    int n, r;
    uint64_t s;
    cout << "Please input n, r: ";
    cin >> n >> r;

    s = choose(n, r);
    cout << s << endl;
    return 0;
}

