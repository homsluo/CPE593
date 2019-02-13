//
// Created by LYQ on 2019/2/12.
//
#include <iostream>
#include <cmath>
using namespace std;

const double phi = (sqrt(5)-1)/2;
double f(double x){
    return x * x - x + 2;
}

double GoldenMeanSearch(double L, double R, double eps){
    double x, y;
    x = L + (R-L) * (1-phi);
    y = R - (R-L) * (1-phi);
    while(fabs(R-L) > eps){
        if (f(x) > f(y)){
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
    return (L+R)/2;
}

int main(){
    double L, R, t;
    cout << "L = ";
    cin >> L;
    cout << "R = " ;
    cin >> R;

    t = GoldenMeanSearch(L, R, 0.5);
    cout << t << ", " << f(t);
    return 0;
}
