#include <iostream>

using namespace std;

template <typename T>
class GrowArray{
private:
    T* data;
    int capacity;
    int used;
    void checkgrow(){
        if(used == capacity)
        {
            T* old = data;
            capacity *= 2;
            data = new T[capacity];
            for(int i = 0; i < capacity; i++)
                data[i] = old[i];
            delete [] old;
        }
    }

public:
    GrowArray():used(0), capacity(1){data = new T[capacity];}
    GrowArray(int i):used(0), capacity(i){data = new T[capacity];}
    ~GrowArray(){delete [] data;}
    void addStart(const T& v)
    {
        checkgrow();
        for(int i = used++; i > 0; i--)
            data[i] = data[i-1];
        data[0] = v;
    }
    void addEnd(const T& v)
    {
        checkgrow();
        data[used++] = v;
    }
    T removeStart()
    {
        T r = data[0];
        for(int i = 1; i <= used; i++)
            data[i-1] = data[i];
        used--;
        return r;
    }
    T removeEnd()
    {
        return data[--used];
    }
    void insert(int pos, const T& v)
    {
        if(pos < 0)
            return;
        checkgrow();
        for(int i = used; i > pos; i--)
            data[i] = data[i-1];
        data[pos] = v;
    }
};

int main(){
    GrowArray<int>A;
    A.addStart(1);
    A.addEnd(2);
    cout << A.removeEnd() << endl;
    cout << A.removeStart();
}