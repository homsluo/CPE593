#include <iostream>

using namespace std;

template <typename T>
class DoubleLikedList
{
private:
    class Node
    {
    public:
        Node* next;
        Node* prev;
        T val;
        Node(Node* next, Node* prev, const T& v):next(next), prev(prev), val(v){}
    };

    Node* head;
    uint32_t size;

public:
    DoubleLikedList():head(nullptr), size(0){}

    T get(int pos) const
    {
        if(pos < 0 || pos >= size)
        {
            cout << "error, position wrong\n";
            return 0;
        }
        Node* p = head;
        for(; pos > 0 && p != nullptr; pos--)
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
            head = new Node(nullptr, nullptr, v);
        }

    }
    void addEnd(const T& v)
    {
        size++;
        if(head != nullptr)
        {
            Node* p = head;
            for(; p->next != nullptr; p = p->next);
            p->next = new Node(nullptr, p, v);
        }
        else
        {
            head = new Node(nullptr, nullptr, v);
        }
    }
    T removeFirst()
    {
        if(head != nullptr && head->next != nullptr)
        {
            size--;
            Node* temp = head;
            head = temp->next;
            head->prev = nullptr;
            T r = temp->val;
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
        else
        {
            cout << "error, empty list\n";
            return 0;
        }
    }
    T removeEnd()
    {
        if(head != nullptr && head->next != nullptr)
        {
            Node* p = head;
            for(; p->next != nullptr; p = p->next);
            Node* q = p->prev;
            q->next = nullptr;
            T r = p->val;
            delete p;
            return r;
        }
        else if(head != nullptr && head->next == nullptr)
        {
            Node* temp = head;
            head = nullptr;
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
            temp->next->prev = temp;
    }
    uint32_t getsize()
    {
        return size;
    }
    ~DoubleLikedList()
    {
        Node* q;
        for(Node* p = head; p->next != nullptr; p = q)
        {
            q = p->next;
            delete p;
        }
    }
};

