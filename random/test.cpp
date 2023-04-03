#include <iostream>
#include <memory>

class A {
    int a;
};

class C {

};

class B {
    int d;
    virtual void a();
    virtual void b();
    C c;
};

class D {
    
};



int main() {
    std::cout << "size of A " << sizeof(A) << std::endl;
    std::cout << "size of B " << sizeof(B) << std::endl;
    std::cout << "size of C " << sizeof(C) << std::endl;
    std::cout << "size of D " << sizeof(D) << std::endl;

    std::shared_ptr<int> s_int = std::make_shared<int>(1);
    std::cout << "size of s_int " << sizeof(s_int) << std::endl;

    return 0;
}