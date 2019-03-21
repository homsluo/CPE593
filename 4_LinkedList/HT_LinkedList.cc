#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        Node *next;
        T val;

        Node(Node *next, const T &v) : next(next), val(v) {}
    };

    Node *head;
    Node *tail;
    uint32_t size;
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
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
            cout << "error, wrong position\n";
            return 0;
        }
        Node* p = head;
        for(;pos < 0 && p->next != nullptr; pos--)
            p = p->next;
        return p->val;
    }
    void addFirst(const T& v)
    {
        size++;
        Node* temp = new Node(head, v);
        if(head != nullptr)
        {
            head = temp;
            return;
        }
        head = tail = temp;
    }
    void addEnd(const T& v)
    {
        size++;
        Node* temp = new Node(nullptr, v);
        if(head != nullptr)
        {
            tail->next = new Node(nullptr, v);
            tail = tail->next;
            return;
        }
        head = tail = temp;
    }
    T removeFirst()
    {
        if(head != nullptr && head->next != nullptr)
        {
            size--;
            Node* temp = head;
            head = head->next;
            T r = temp->val;
            delete temp;
            return r;
        }
        else if(head != nullptr && head->next == nullptr)
        {
            size--;
            Node* temp = head;
            head = tail = nullptr;
            T r = temp->val;
            delete temp;
            return r;
        }
        cout << "error, empty list\n";
        return 0;
    }
    T removeEnd()
    {
        if(head != nullptr && head->next != nullptr)
        {
            size--;
            Node* p = head;
            Node* q = p->next;
            for(; q->next != nullptr; p = q, q = q->next);
            p->next = nullptr;
            T r = q->val;
            delete q;
            return r;
        }
        else if(head != nullptr && head->next == nullptr)
        {
            size--;
            Node* temp = head;
            head = tail = nullptr;
            T r = temp->val;
            delete temp;
            return r;
        }
        cout << "error, empty list\n";
        return 0;
    }
    void insert(int pos, const T& v)
    {
        if(pos < 0 || pos >= size)
        {
            cout << "error: wrong position\n"
            return;
        }
        size++;
        Node* p = head;
        for(;pos > 0; pos--)
            p = p->next;
        Node* temp = new Node(p->next, v);
        p->next = temp;
        if(temp->next == nullptr)
            tail = temp;
    }
};