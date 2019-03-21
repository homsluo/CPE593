//
// Created by KimLAB on 3/1/2019.
//
#include <iostream>
using namespace std;

class Point{
public:
    double x, y;
    Point(double x, double y):x(x),y(y){}
};

template <typename T>
class D2_GrowArray{
private:
    T* data;
    int capacity_w;
    int capacity_h;
    int used_w;
    int used_h;
    void grow(){
        if(used_h == capacity_h || used_w == capacity_w){
            T* old = data;
            data = new T[capacity_h*2][capacity_w*2];
            for(int i = 0; i < capacity_h; i++){
                for(int j = 0; j < capacity_w; j++){
                    data[i][j] = old[i][j];}}
            delete [] old;
        }
    }

public:
    D2_GrowArray():
    used_w(0), used_h(0), capacity_w(1), capacity_h(1)
    {data = new T[capacity_h][capacity_w];}

    D2_GrowArray(int initialSize):
    used_h(0), used_w(0), capacity_h(initialSize), capacity_w(initialSize)
    {data = new T[capacity_h][capacity_w]; }

    ~D2_GrowArray(){
        delete [] data;
    }
    void addEnd
};