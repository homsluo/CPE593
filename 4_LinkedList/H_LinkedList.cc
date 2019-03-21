#include <iostream>

using namespace std;

template <typename T>
class LinkedList{
private:
    class Node{
    public:
        Node* next;
        T val;
        Node(Node* next, const T& v):next(next), val(v){}
    };
    Node* head;
    uint32_t size;
public:
    LinkedList():head(nullptr), size(0){}
    ~LinkedList()
    {
        Node* p = head;
        Node* q;
        for(; p != nullptr; p = q)
        {
            q = p->next;
            delete p;
        }
    }
    T get(int pos) const
    {
        if(pos < 0 || pos >= size)
        {
            cout << "error: position wrong\n";
            return 0;
        }
        Node* p = head;
        for(;pos > 0; pos--)
            p = p->next;
        return p->val;
    }
    void addFirst(const T& v)
    {
        size++;
        head = new Node(head, v);
    }
    void addEnd(const T& v)
    {
        size++;
        if(head != nullptr)
        {
            Node* p = head;
            for(; p->next != nullptr; p = p->next);
            p->next = new Node(nullptr, v);
            return;
        }
        head = new Node(nullptr, v);
    }
    T removeFirst()
    {
        if(head != nullptr)
        {
            size--;
            Node* temp = head;
            head = head->next;
            T r = temp->val;
            delete temp;
            return r;
        }
        cout << "error: empty list\n";
        return 0;
    }
    T removeEnd()
    {
        if(head != nullptr && head->next != nullptr)
        {
            size--;
            Node* p = head;
            Node* q = p->next;
            for(;q->next != nullptr; p = q, q = q->next);
            p->next = nullptr;
            T r = q->val;
            delete q;
            return r;
        }
        else if(head != nullptr && head->next == nullptr)
        {
            size--;
            Node* temp = head;
            head = nullptr;
            T r = temp->val;
            delete temp;
            return r;
        }
        cout << "error: empty list\n";
        return 0;
    }
    void insert(int pos, const T& v)
    {
        if(pos < 0 || pos >= size)
        {
            cout << "error: wrong position\n";
            return;
        }
        Node* p = head;
        for(; pos > 0; pos--)
            p = p->next;
        Node* temp = new Node(p->next, v);
        p->next = temp;
    }
    bool isEmpty() const
    {
        if(size > 0)
            return false;
        return true;
    }
};

class Stack{
private:
    LinkedList<int>impl;
public:
    void push(int v){impl.addFirst(v);}//addEnd
    int pop(){return impl.removeFirst();}//removeEnd
    bool isEmpty() const{return impl.isEmpty();}
};
class Queue
{
private:
    LinkedList<int>impl2;
public:
    void enqueue(int v){impl2.addEnd(v);}//addFirst
    int dequeue(){return impl2.removeFirst();}//removeEnd
    bool isEmpty() const{return impl2.isEmpty();}
};

//HT_D:addFirst O(1), addEnd O(1), removeFirst O(1), removeEnd O(1)
//H_D:addFirst O(1), addEnd O(n), removeFirst O(1), removeEnd O(n)
//HT_L:addFirst O(1), addEnd O(1), removeFirst O(1) removeEnd O(n)
//H_L:addFirst O(1), addEnd O(n), removeFirst O(1) removeEnd O(n)
//GA:addFirst O(n), addEnd O(1), removeFirst O(n), removeEnd O(1)