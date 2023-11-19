#include <iostream>

struct CallFunction {
    void operator() (int b) const {
        std::cout << "Hello world" << b << std::endl;
    }
};
// CallFunction callFunction;

void function1(int a) {
    std::cout << "function1 " << a << std::endl;
}

struct cout {
    std::ostream os_;

    std::ostream& operator<<(std::ostream& os) {
        os.;
    }

    std::ostream& operator<<(const std::string& str) {
        os_ << str;
        return os_;
    }
};

std::ostream& operator<<(std::ostream& os, cout obj) {
    return obj << os;
}


int main() {
    // std::vector<void(*)(int)> functionList;
    CallFunction a;
    std::vector<std::function<void(int)>> functionList;
    functionList.push_back(function1);
    functionList.push_back([](int a) {std::cout << "defined lambda function " << a << std::endl;});
    auto lamb = [](int a) {std::cout << "auto lamb function " << a << std::endl;};
    functionList.push_back(lamb);


    for (auto func : functionList) {
        func(123);
    }

    // std::cout << "static function size " << sizeof(function1) << std::endl;
    // std::cout << "static function address " << &function1 << " " << &main << " " << &a << " " << &(a.operator()) << std::endl;
    return 0;
}