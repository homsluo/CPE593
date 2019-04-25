#include <iostream>

using namespace std;

class GrowArray{
private:
    int* data;
    int capacity;
    int used;
    void checkgrow(){
        if(used == capacity) {
            capacity *= 2;
            int *old = data;
            data = new int[capacity];
            for (int i = 0; i < used; i++)
                data[i] = old[i];
            delete[] old;
        }
    }

public:
    GrowArray():data(nullptr), capacity(1), used(0){}
    GrowArray(int i):data(new int [i]), capacity(i), used(0){
        for(int p = 0; p < i; p++)
            data[p] = 0;
    }
    ~GrowArray(){delete [] data;}
    void addStart(int v){
        checkgrow();
        for(int i = used++; i > 0; i--)
            data[i] = data[i-1];
        data[0] = v;
    }
    void addEnd(int v){
        checkgrow();
        data[used] = v;
        used++;
    }
    int removeStart(){
        int v = data[0];
        for(int i = 0; i < used; i++)
            data[i] = data[i+1];
        used--;
        return v;
    }
    int removeEnd(){
        return data[--used];
    }
    void insert(int v, int pos){
        if(pos < 0)
            return;
        checkgrow();
        for(int i = used; i > pos; i--)
            data[i] = data[i-1];
        data[pos] = v;
        used++;
    }

};
