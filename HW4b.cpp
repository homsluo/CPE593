/*
	 Author: Yuqing Luo

	 HW4b - Linked List class
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

class LinkedList2{
private:
    class Node{
    public:
        Node* next;
        int val;

        Node(Node* n, int v):next(n), val(v){}
    };
    Node* head;
    Node* tail;
    uint32_t size;
public:
    LinkedList2():head(nullptr), tail(nullptr), size(0){}
    ~LinkedList2(){
        Node* p = head;
        Node* q;
        for(; p != nullptr; p = q){
            q = p->next;
            delete p;
        }
    }

    int get(int pos)const{
        if(pos < 0 || pos >= size){
            cout << "wrong position" << '\n';
            return 0;
        }
        else{
            Node* p = head;
            for(; pos > 0; pos--,p = p->next);
            return p->val;
        }
    }
    void addStart(int v){
        if(size == 0){
            head = tail = new Node(nullptr, v);
        }
        else{
            head = new Node(head, v);
        }
        size++;
    }

    void addEnd(int v){
        if(size == 0){
            head = tail = new Node(nullptr, v);
        }
        else{
            tail->next = new Node(nullptr, v);
            tail = tail->next;
        }
        size++;
    }

    void removeStart(){
        if(size == 0){
            return;
        }
        else if(size == 1){
            Node* temp = head;
            head = tail = nullptr;
            delete temp;
            size--;
        }
        else{
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }

    void removeEnd(){
        if(size == 0){
            return;
        }
        else if(size == 1){
            Node* temp = tail;
            head = tail = nullptr;
            delete temp;
            size--;
        }
        else{
            Node* p = head;
            Node* q = p->next;
            for(; q ->next != nullptr; p = q, q = q->next);
            p->next = nullptr;
            delete q;
            size--;
        }
    }

    void OUTPUT(){
        Node* p = head;
        for(; p != nullptr; p = p->next)
            cout << p->val << ", ";
    }

    void ADD_FRONT(int s, int d, int e){
        while(s <= e){
            addStart(s);
            s += d;
        }
    }

    void ADD_BACK(int s, int d, int e){
        while(s <= e){
            addEnd(s);
            s += d;
        }
    }

    void REMOVE_FRONT(int n){
        while(n > 0){
            removeStart();
            n--;
        }
    }

    void REMOVE_END(int n){
        while(n > 0){
            removeEnd();
            n--;
        }
    }

    class Iterator{
    private:
        Node* current;
    public:
        Iterator(const LinkedList2& list){
            current = list.head;
        }
        bool operator !() const{
            return current != nullptr;
        }

        void operator ++(){
            current = current->next;
        }

        int operator *() const{
            return current->val;
        }
    };
};

int main(){
    LinkedList2 a;
    ifstream f("HW4b.txt");
    string p, w;
    int call[2];
    int s, d, e, j, temp;
    char buf[1024];
    while(!f.eof()){
        f.getline(buf, sizeof(buf));
        istringstream linstr(buf);
        linstr >> p >> w;
        if(p == "ADD_FRONT"){
            j = 0;
            for(int i = 0; i < w.length(); i++){
                if(w[i]-58 == 0){
                    call[j] = i;
                    j++;
                }
            }
            temp = 0, s = 0;
            for(int i = call[0]; i > 0; i--){
                s += (w[temp]-48)*pow(10, i-1);
                temp++;
            }
            d = 0,temp++;
            for(int i = call[1]-1; i > call[0]; i--){
                d += (w[temp]-48)*pow(10, i-call[0]-1);
                temp++;
            }
            e = 0, temp++;
            for(int i = w.length()-1; i > call[1]; i--){
                e += (w[temp]-48)*pow(10, i-call[1]-1);
                temp++;
            }
            a.ADD_FRONT(s, d, e);
        }
        else if(p == "ADD_BACK"){
            j = 0;
            for(int i = 0; i < w.length(); i++){
                if(w[i]-58 == 0){
                    call[j] = i;
                    j++;
                }
            }
            temp = 0, s = 0;
            for(int i = call[0]; i > 0; i--){
                s += (w[temp]-48)*pow(10, i-1);
                temp++;
            }
            d = 0,temp++;
            for(int i = call[1]-1; i > call[0]; i--){
                d += (w[temp]-48)*pow(10, i-call[0]-1);
                temp++;
            }
            e = 0, temp++;
            for(int i = w.length()-1; i > call[1]; i--){
                e += (w[temp]-48)*pow(10, i-call[1]-1);
                temp++;
            }
            a.ADD_BACK(s, d, e);
        }
        else if(p == "OUTPUT"){
            for(LinkedList2::Iterator i = a; !i; ++i)
                cout << *i << ' ';
            cout << endl;
        }
        else if(p == "REMOVE_FRONT"){
            a.REMOVE_FRONT(w[0]-48);
        }
        else if(p == "REMOVE_BACK"){
            a.REMOVE_END(w[0]-48);
        }
    }
}