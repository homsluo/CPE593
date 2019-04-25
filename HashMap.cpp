#include <iostream>
#include <cstring>

using namespace std;

//class LinkedList{
//    class Node{
//    public:
//        Node* next;
//        string word;
//        Node(Node* n, const string& w):next(n), word(w){}
//    };
//    Node* head;
//    uint32_t L_size;
//public:
//    LinkedList():head(nullptr),L_size(0){}
//    ~LinkedList(){
//        Node* p = head;
//        Node* q;
//        for(;p != nullptr; p = q){
//            q = p->next;
//            delete p;
//        }
//    }
//    void addStart(const string& w){
//        L_size++;
//        head = new Node(head, w);
//    }
//    void addEnd(const string& w){
//        if(L_size == 0)
//            head = new Node(nullptr, w);
//        else{
//            Node* p = head;
//            for(;p->next != nullptr; p = p->next);
//            p->next = new Node(nullptr, w);
//        }
//    }
//};

class LineadChaining{
private:
    class Bucket{
    public:
        class Node{
        public:
            Node* next;
            string key;
            Node(Node* n, const string& k):next(n), key(k){};
        };
        Node* head;
        uint32_t Bsize;
        Bucket():head(nullptr), Bsize(0){}
        ~Bucket(){
            Node* p = head;
            Node* q;
            for(;p != nullptr; p = q){
                q = p->next;
                delete p;
            }
        }
        void addStart(const string& key){
            head = new Node(head, key);
            Bsize++;
        }
    };
    Bucket* table;
    uint32_t size;
    uint32_t used;
    uint32_t hash(const string& key){
        uint32_t sum = key.length();
        for(int i = 0; i < key.length(); i++){
            sum = (sum << 5) + (sum >> 17) + key[i];
        }
        return sum & (size - 1);
    }

public:
    LineadChaining(uint32_t initialSize = 1024)
    :size(initialSize), used(0){
        table = new Bucket[initialSize];
    }
    ~LineadChaining(){
        delete [] table;
    }
    void add(const string& key){
        int pos = hash(key);
        Bucket::Node* p = table[pos].head;
        while(p != nullptr){
            if(p->key == key){
                p->key = key;
                return;
            }
            p = p->next;
        }
        table[pos].addStart(key);
    }

    bool find(const string& key){
        int pos = hash(key);
        Bucket::Node* p = table[pos].head;
        while(p != nullptr){
            if(p->key == key)
                return true;
            p = p->next;
        }
        return false;
    }

    void get(){
        cout << table[0].head->key;
    }
};

int main(){
    LineadChaining hashmap;
    hashmap.add("cat");
    cout << hashmap.find("cat") << endl;
    cout << hashmap.find("dog") << endl;
    hashmap.get();
}