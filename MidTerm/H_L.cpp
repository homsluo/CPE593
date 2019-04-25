#include <iostream>

using namespace std;

class LinkedList{
private:
    class Node{
    public:
        int val;
        Node* next;
        Node(Node* next, int val):next(next), val(val){}
    };
    Node* head;
    uint32_t size;
public:
    LinkedList():head(nullptr), size(0){}
    ~LinkedList(){
        Node* p = head;
        Node* q;
        for(; p != nullptr; p = q){
            q = p->next;
            delete p;
        }
    }

    int get(int pos){
        if(pos < 0 || pos >= size)
            return 0;
        Node* p = head;
        for(; pos > 0; pos--)
            p = p->next;
        return p->val;
    }

    void addStrat(int v){
        size++;
        head = new Node(head, v);
    }

    void addEnd(int v){
        size++;
        if(size == 0)
            head = new Node(nullptr, v);
        else{
            Node* p = head;
            for(; p->next != nullptr; p = p->next);
            p->next = new Node(nullptr, v);
        }
    }

    int removeFirst(){
        if(size == 0)
            return 0;
        else{
            size--;
            Node* temp = head;
            head = head->next;
            int v = temp->val;
            delete temp;
            return v;
        }
    }

    int removeEnd(){
        if(size == 0)
            return 0;
        if(size == 1){
            Node* temp = head;
            head = nullptr;
            int v = temp->val;
            delete temp;
            return v;
        }
        else{
            Node* p = head;
            Node* q = p->next;
            for(; q->next != nullptr; p = p->next, q = q->next);
            p->next = nullptr;
            int v = q->val;
            delete q;
            return v;
        }
    }

    void insert(int v, int pos){
        if(pos < 0 || pos >= size)
            return;
        Node* p = head;
        for(; pos > 0; pos--)
            p = p->next;
        Node* temp = new Node(p->next, v);
        p->next = temp;
    }
};
