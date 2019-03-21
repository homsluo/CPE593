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
            data = new T[capacity * 2];
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
    void addEnd(T v) {
        grow();
        data[used++] = v;
    }
    void addStart(T v) {
        grow();
        for(int i = used++; i > 0; i--)
            data[i] = data[i-1];
        data[0] = v;
    }
    void insert(int i, T v) {
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
        for(int i = --used; i >0; i--)
            data[i-1] = data[i];
    }
    void remove(int i) {
        for(int j = i; j < --used; j++)
            data[j] = data[j+1];
    }
    int size() const {
        return used;
    }// return how many elements in the list

    int* FirstPointer(){
        return data;
    }
    int Used(){
        return used;
    }
    void printUsed(){
        cout << used << '\n';
    }
};

template <typename T>
class LinkedList{
private:
    class Node{
    public:
        int* val;
        Node* next;

        Node(int* v, Node* n): val(v), next(n){}
    };

    Node* head;

public:
    LinkedList(){
        head = NULL;
    }
    void addStart(int* v){
        head = new Node(v, head);
    }
    void addEnd(int* v){
        Node* temp = new Node(v, NULL);
        Node* p;
        if(head == NULL) {
            head = temp;
            return;
        }
        for(p = head; p->next != NULL; p = p->next)
            p->next = temp;
    }
    void insert(int pos, int* v){
        Node* p = head;
        while(pos > 0){
            p = p->next;
            pos--;
        }
        p->next = new Node(v, p->next); //first create the Node, then make p point to it
    }
    int* removeStart(){
        Node* temp = head;
        head = head->next;
        return temp->val;
    }
    int* removeEnd(){
        Node* p = head;
        Node* q = p->next;
        if(q == NULL){
            int* v = head->val;
            head = NULL;
            return v;
        }

        for(;q->next != NULL; p = q, q = q->next){
            p->next = NULL;
            return q->val;
        }
    }

    void print(GrowArray<int> a){
        int*p = this->head->val;
        for(int i = 0; i < a.Used(); i++){
            cout << *p << ", ";
            p++;
        }
    }

    friend ostream&operator <<(ostream& s, const LinkedList& list){
        for (Node* p = list.head; p!= nullptr; p = p->next)
            s << p->val << ' ';
        return s;
    }

};

int main(){
    LinkedList<int*> a;
    GrowArray<int>P1(2);
    P1.addEnd(10);
    P1.addEnd(20);
    P1.printUsed();
    a.addEnd(P1.FirstPointer());
    cout << a << '\n';
    a.print(P1);
    return 0;
}