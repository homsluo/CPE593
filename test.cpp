#include <iostream>

using namespace std;

class A{
private:
    int x;
public:
    A(int x):x(x){cout << "a";}
    A(): x(3) {cout << "b" << x;}
    ~A() {cout << "c\n";}
    void f() const {cout << "d";}
};
void f(){
    A a1;
    a1.f();
}
int main(){
    f();
    A a2(5);
}