#include <iostream>

using namespace std;

template <typename T>
class DoubleLinkedList {
private:
    class Node {
    public:
        Node *next;
        Node *prev;
        T val;

        Node(Node *next, Node *prev, const T& v) : next(next), prev(prev), val(v) {}
    };

    Node *head;
    Node *tail;
    uint32_t size;  //need to be initialized
public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    T get(int pos) const
    {
        if(pos < 0 || pos >= size)
        {
            cout << "error, position wrong\n";
            return 0;
        }
        Node* p = head;
        for(; pos > 0; pos--)
            p = p->next;
        return p->val;
    }
    void addFirst(const T& v)
    {
        size++;
        if(head != nullptr)
        {
            Node* temp = new Node(head, nullptr, v);
            head->prev = temp;
            head = temp;
        }
        else
        {
            head = tail = new Node(nullptr, nullptr, v);
        }
    }
    void addEnd(const T& v)
    {
        size++;
        if(head != nullptr)
        {
            Node* temp = new Node(nullptr, tail, v);
            tail->next = temp;
            tail = temp;
        }
        else
        {
            head = tail = new Node(nullptr, nullptr, v);
        }
    }
    T removeFirst()
    {
        if(head != nullptr && head->next != nullptr)//size>=2
        {
            size--;
            Node* temp = head;
            head = head->next;
            head->prev = nullptr;
            T r = temp->val;
            delete temp;
            return r;
        }
        else if(head != nullptr && head->next == nullptr)//size == 1
        {
            size--;
            Node* temp = head;
            head = tail = nullptr;
            T r = temp->val;
            delete temp;
            return r;
        }
        else
        {
            cout << "error, empty list\n";
            return 0;
        }
    }
    T removeEnd()
    {
        if(head != nullptr && head->next != nullptr)//size >= 2
        {
            size--;
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            T r = temp->val;
            delete temp;
            return r;
        }
        else if(head != nullptr && head->next == nullptr)// size == 1
        {
            size--;
            Node* temp = tail;
            tail = head = nullptr;
            T r = temp->val;
            delete temp;
            return r;
        }
        else
        {
            cout << "error, empty list\n";
            return 0;
        }
    }
    void insert(int pos, const T& v)
    {
        if(pos < 0 || pos >= size)
        {
            cout << "error: wrong position\n";
            return;
        }
        size++;
        Node* p = head;
        for(; pos > 0; pos--)
            p = p->next;
        Node* temp = new Node(p->next, p, v);
        p->next = temp;
        if(temp->next != nullptr)
        {
            temp->next->prev = temp;
            return;
        }
        else
        {
            tail = temp;
        }
    }
    uint32_t getSize()
    {
        return size;
    }
    ~DoubleLinkedList()
    {
        Node* q;
        for(Node* p = head; p != nullptr; p = q)
        {
            q = p->next;
            delete p;
        }
    }
    //copy constructor
    DoubleLinkedList(const DoubleLinkedList& orig)
    {
        if(orig.head == nullptr)
        {
            head = nullptr;
            return;
        }
        head = new Node(nullptr, nullptr, orig.head->val);
        Node* src = orig.head->next;
        Node* dest = head;
        while(src != nullptr)
        {
            dest->next = new Node(nullptr, dest, src->val);
            dest = dest->next;
            src = src->next;
        }
    }
    //move constructor
    DoubleLinkedList(const DoubleLinkedList&& orig)
    {
        head = orig.head;
        orig.head = nullptr;
    }
};