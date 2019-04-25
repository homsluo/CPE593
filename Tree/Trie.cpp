/*
	 Author: Yuqing Luo

	 Trie Dictionary
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

class Trie{
private:
    class Node{
    public:
        Node* next[26];
        bool isWord;
    };
    Node* root;
public:
    Trie(){
        root = new Node();
        for(int i = 0; i < 26; i++)
            root->next[i] = nullptr;
    }
    void insert(const char word[]){
        Node* p = root;
        for(int i = 0; i < strlen(word); i++){
            if(p->next[word[i]-97] == nullptr)
                p->next[word[i]-97] = new Node();
            p = p->next[word[i]-97];
        }
        p->isWord = true;
    }

    bool contains(const char word[]){
        Node* p = root;
        for(int i = 0; i < strlen(word); i++){
            if(p->next[word[i]-97] == nullptr)
                return false;
            p = p->next[word[i]-97];
        }
        return p->isWord;
    }

    bool containsPrefix(const char word[]){
        Node* p = root;
        for(int i = 0; i < strlen(word); i++){
            if(p->next[word[i]-97] == nullptr)
                return false;
            p = p->next[word[i]-97];
        }
        return true;
    }
};

int main(){
    Trie a;
    char buf[1024];
    ifstream f("dict.txt");
    if(!f){
        cout << "open failed" << endl;
        return 0;
    }
    while(!f.eof()){
        f.getline(buf, sizeof(buf));
        a.insert(buf);
    }

    ifstream p("words.dat");
    if(!p){
        cout << "open failed" << endl;
        return 0;
    }
    while(!p.eof()){
        p.getline(buf, sizeof(buf));
        cout << a.contains(buf) << ' ';
    }
    cout << endl;
    cout << a.containsPrefix("cata") << endl;
}