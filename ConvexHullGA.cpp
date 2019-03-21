/*
	 Author: Yuqing Luo

	 HW4a - GrowArray
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Point
{
private:
    double x, y;
public:
    Point(double x, double y): x(x), y(y){};

    friend ostream& operator <<(ostream& s, Point a);
};

ostream& operator << (ostream& s, Point a)
{
    s << "(" << a.x << ", " << a.y << ")";
    return s;
}

template <typename T>
class GrowArray
{
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
    GrowArray():used(0), capacity(1) {data = new T[capacity];}
    GrowArray(int i):used(0), capacity(i) {data = new T[capacity];}
    ~GrowArray()
    {
        delete [] data;
    }
    void addEnd(T v)
    {
        checkgrow();
        data[used++] = v;
    }
    void addStart(T v)
    {
        checkgrow();
        for(int i = used++; i > 0; i--)
            data[i] = data[i-1];
        data[0] = v;
    }
    void insert(int pos,T v)
    {
        if(pos < 0)
        {
            cout << "Error Position\n";
            return;
        }
        if(pos < used)
        {
            for(int i = used++; i > pos; i--)
            {
                data[i] = data[i-1];
            }
            data[pos] = v;
        }
        data[pos] = v;
    }
    T remove(int pos)
    {
        if(pos < 0)
        {
            cout << "Position error\n";
            return;
        }
        if(pos < used)
        {
            T r = data[pos];
            for(int i = pos; i < used-1; i++)
            {
                data[i] = data[i+1];
            }
            used--;
            return r;
        }
        T r = data[pos];
        data[pos] = NULL;
        return r;
    }
    T removeEnd()
    {
        return data[--used];
    }
    T removeStart()
    {
        T r = data[0];
        for(int i = 0; i < used-1; i++)
        {
            data[i] = data[i+1];
        }
        return r;
    }
    int size() const
    {
        return used;
    }
    void setNullptr()
    {
        T* old = data;
        data = new T[capacity];
        for(int i = 0; i < capacity; i++)
        {
            data[i] = nullptr;
        }
        delete [] old;
    }
    int Numcapacity()
    {
        return capacity;
    }
    T* begin()
    {
        return data;
    }
    void setCapacity(int i)
    {
        capacity = i*i;
    }
    void print()
    {
        for(int i = 0; i < capacity; i++)
        {
            cout << data[i] << '\n' ;
        }
    }
    void printpos(int pos)
    {
        if(data[pos] == nullptr)
            cout << "0, ";
        else
            cout << *data[pos] << ", ";
    }
};

class ConvexHull
{
private:
    int size;
    double xmin, xmax, ymin, ymax;
    GrowArray<Point*>Cvx;
public:
    ConvexHull(int i):size(i){Cvx.setCapacity(i); Cvx.setNullptr();}

    void read(const string& n)
    {
        ifstream f(n);
        if(!f)
        {
            cout << "Open failed!\n";
            return;
        }

        vector<double>Px;
        vector<double>Py;
        while(!f.eof())
        {
            double x, y;
            f >> x >> y;
            Px.push_back(x);
            Py.push_back(y);
            f.get();
            if(f.peek() == '\n')
                break;
        }
        xmin = xmax = Px[0];
        ymin = ymax = Py[0];
        for(auto i:Px)
        {
            if(i < xmin)
                xmin = i;
            if(i > xmax)
                xmax = i;
        }
        for(auto i:Py)
        {
            if(i < ymin)
                ymin = i;
            if(i > xmax)
                ymax = i;
        }
        const double XperBox = 1/(xmax-xmin);
        const double YperBox = 1/(ymax-ymin);
        int p = 0, q = 0;
        int pos;
        for(int i = 0; i < Px.size(); i++)
        {
            int cell_i, cell_j;
            cell_i = (Py[p]-ymin) * YperBox * (size-1);
            cell_j = (Px[q]-xmin) * XperBox * (size-1);
            pos = (size-1-cell_i) * size + cell_j;
            cout << pos << ", ";
            Point* a = new Point(Px[q], Py[p]);
            Cvx.insert(pos, a);
            p++,q++;
        }
    }
    void printAllListSizes(){
        Point** p = Cvx.begin();
        cout << endl;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(*p != nullptr)
                {
//                    cout << **p;
                    cout << "1" << ", ";
                    p++;
                }
                else
                {
                    cout << "0" << ", ";
                    p++;
                }
            }
            cout << '\n';
        }
    }
    void printMinMax()
    {
        cout << "x_Min: " << xmin << ", x_Max: " << xmax << '\n';
        cout << "y_Min: " << ymin << ", y_Max: " << ymax << '\n';
    }
    void printPerimeterClockWiseOrder()
    {
        int j = 0;
        for(int i = 0; i < 4*(size-1); i++)
        {
            Cvx.printpos(j);
            if(i < 15)
                j++;
            else if(i < 30)
                j += 16;
            else if(i < 45)
                j --;
            else if(i < 60)
                j -= 16;
        }
    }

};

int main()
{
    ConvexHull ch(16);
    ch.read("convexhullpoints.dat");
    ch.printAllListSizes();
    ch.printMinMax();
    ch.printPerimeterClockWiseOrder();
}
