#include <iostream>
using namespace std;

class Point {
public:
    double x,y;
    Point(double x, double y): x(x), y(y){}
};


template<typename T>
class GrowArray {
private:
    T* data;
    int capacity;
    int used;
    void grow() {
        if (used == capacity) {
            T* old = data;
            capacity *= 2;
            data = new T[capacity];
            for(int i = 0; i < capacity; i++)
                data[i] = old[i];
            delete [] old;
        }
    }
public:
    GrowArray():used(0), capacity(1) {data = new T[capacity];}
    GrowArray(int initialSize):used(0), capacity(initialSize) {data = new T[capacity];} // set initial capacity
    ~GrowArray(){
        delete [] data;
    }
    void addEnd(const T& v) {
        grow();
        data[used++] = v;
    }
    void addStart(const T& v) {
        grow();
        for(int i = used++; i > 0; i--)
            data[i] = data[i-1];
        data[0] = v;
    }
    void insert(int i, const T& v) {
        if(i < 0 || i >= used){
            cout << "Position error!";
            return;
        }
        grow();
        for(int j = used++; j > i; j--)
            data[j] = data[j-1];
        data[i] = v;
    }
    void removeEnd() {
        used--;
    }
    void removeStart() {
        for(int i = 0; i < used; i++)
            data[i] = data[i+1];
        used--;
    }
    void remove(int i) {
        for(int j = i; j < used; j++)
            data[j] = data[j+1];
        used--;
    }
    int size() const {
        return used;
    }// return how many elements in the list
    void print(){
        T* t = data;
        for(int i = 0; i < capacity; i++) {
            cout << *t << ", ";
            t++;
        }
    }
    void setZrto(){
        for(int i = 0; i < capacity; i++)
            data[i] = 0;
    }
    int Numcapacity(){
        return capacity;
    }
};

int main(){
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    GrowArray<int>P1(2);
    P1.addEnd(a);
    P1.addEnd(b);
    P1.addStart(c);
    P1.insert(1,d);
    P1.addEnd(5);
//    P1.removeEnd();
//    P1.removeStart();
    P1.setZrto();
    cout << P1.size() << endl;
    cout << P1.Numcapacity()<<endl;
    P1.print();
}

