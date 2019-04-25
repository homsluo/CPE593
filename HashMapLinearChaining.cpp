/*
	 Author: Yuqing Luo

	 HashMapLinearChaining
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

class LinkedList{
public:
    class Node{
    public:
        Node* next;
        string key;
        Node(Node* n, const string& k):next(n), key(k){}
    };
    Node* head;
    uint32_t Lsize;
    LinkedList():head(nullptr), Lsize(0){}
    ~LinkedList(){
        Node* p = head;
        Node* q;
        for(;p != nullptr; p = q){
            q = p->next;
            delete p;
        }
    }
    void addStart(const string& k){
        head = new Node(head, k);
        Lsize++;
    }
};

class HashMapLinearChaining{
private:
    LinkedList* table;
    uint32_t size;
    uint32_t used;
    uint32_t hash(const string& key){
        uint32_t sum = key.length();
        for(int i = 0; i < key.length(); i++){
            sum = (sum << 5) + (sum >> 17) + key[i];
        }
        return sum % (size - 1);
    }
    void grow(){
        used = 0;
        LinkedList* old = table;
        size = size*2;
        table = new LinkedList[size];
        for (uint32_t i = 0; i < size/2; i++) {
            if (old[i].Lsize != 0) {
                LinkedList::Node *q = old[i].head;
                for (; q != nullptr; q = q->next) {
                    add(q->key);
                }
            }
        }
        delete [] old;
    }

public:
    HashMapLinearChaining(uint32_t initialSize = 1024)
    :size(initialSize), used(0){
        table = new LinkedList[size];
    }
    ~HashMapLinearChaining(){
        delete [] table;
    }
    void add(const string& key){
        int pos = hash(key);
        LinkedList::Node* p = table[pos].head;
        if(p == nullptr)
            used++;
        while(p != nullptr){
            if(p->key == key){
                p->key = key;
                return;
            }
            p = p->next;
        }
        table[pos].addStart(key);
        if(size * 0.7 <= used){
            grow();
        }
    }

    bool find(const string& key){
        int pos = hash(key);
        LinkedList::Node* p = table[pos].head;
        while(p != nullptr){
            if(p->key == key)
                return true;
            p = p->next;
        }
        return false;
    }

    void hist(){
        cout << endl << "insert" << '\t' << "count" << endl;
        for(int i = 0; i < size; i++){
            cout << i << '\t' << table[i].Lsize << endl;
        }
    }
};

int main(){
    HashMapLinearChaining dict;
    char buf[1024];
    ifstream f("dict.txt");
    if(!f){
        cout << "open failed" << endl;
        return 0;
    }
    while(!f.eof()){
        f.getline(buf, sizeof(buf));
        dict.add(buf);
    }

    ifstream p("words.dat");
    if(!p){
        cout << "open failed" << endl;
        return 0;
    }
    while (!p.eof()){
        p.getline(buf, sizeof(buf));
        if(dict.find(buf))
            cout << buf << " true" << endl;
        else
            cout << buf << " false" << endl;
    }
//    dict.hist();
}