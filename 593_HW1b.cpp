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
    return choose (n - 1, r - 1) + choose (n - 1, r);
};

int main(){
    int n, r;
    uint64_t s;
    cin >> n >> r;

    s = choose(n, r);
    cout << s << endl;
    return 0;
}