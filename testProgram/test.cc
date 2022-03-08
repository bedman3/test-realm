#include <iostream>

struct Car {
    Car() : price(20000) {}
    Car(double b) : price(b * 1.1) {}
    double price;
};

struct Toyota : public virtual Car {
    Toyota(double b) : Car(b) {}
};

struct Prius : public Toyota {
    Prius(double b) : Toyota(b) {}
};

int main() {
    Prius p(30000);
    std::cout << p.price << std::endl;
}

