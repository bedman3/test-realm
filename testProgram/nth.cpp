#include <iostream>


class Count {
    int size_;
public:
    int size() { std::cout << "Called size" << std::endl; return this->size_; }

    Count(int size) : size_(size) {};
    ~Count() {};
};

int main() {
    Count obj(5);

    for (int i = 0; i < obj.size(); ++i) {
        std::cout << "Testing inside loop" << std::endl;
    }
}
