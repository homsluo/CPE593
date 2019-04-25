#include <iostream>

using namespace std;

class BinaryTree{
private:
    class Node{
    public:
        int val;
        Node* left;
        Node* right;
        Node* parent;
        Node(int v, Node* L, Node* R, Node* P)
        : val(v), left(L), right(R), parent(P){}
        void inorder(){
            if(left != nullptr)
                left->inorder();
            cout << val << ' ';
            if(right != nullptr)
                right->inorder();
        }

        void preorder(){
            cout << val << ' ';
            if(left != nullptr)
                left->preorder();
            if(right != nullptr)
                right->preorder();
        }

        void postorder(){
            if(left != nullptr)
                left->postorder();
            if(right != nullptr)
                right->postorder();
            cout << val << ' ';
        }
    };
    Node* root;
public:
    BinaryTree(): root(nullptr){}
    void add(int v){
        if(root == nullptr){
            root = new Node(v, nullptr, nullptr, nullptr);
            return;
        }
        Node* p = root;
        while(true)
            if(v <= p->val){
                if(p->left == nullptr){
                    p->left = new Node(v, nullptr, nullptr, p);
                    return;
                }
                p = p->left;
            }
            else{
                if(p->right == nullptr){
                    p->right = new Node(v, nullptr, nullptr, p);
                    return;
                }
                 p = p->right;
            }
    }

    void inorder(){
        if( root != nullptr)
            root->inorder();
    }
    void preorder(){
        if(root != nullptr)
            root->preorder();
    }
    void postorder(){
        if(root != nullptr)
            root->postorder();
    }
};

int main(){
    BinaryTree t;
    t.add(3);
    t.add(1);
    t.add(4);
    t.add(1);
    t.add(5);
    t.add(9);
    t.add(2);
    t.inorder();  cout << '\n';
    t.preorder();  cout << '\n';
    t.postorder();  cout << '\n';
}