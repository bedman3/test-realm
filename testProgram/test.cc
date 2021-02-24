#include <iostream>
#include <thread>
#include <cstring>
#include <ctime>
#include <chrono>

#define EACH_THREAD_ITER 1e9
#define MAX_THREAD 3

void incrementManyTimes(int &number) {
    for (int i = 0; i < EACH_THREAD_ITER; ++i) {
        ++number;
    }
}

int main() {
    int number = 0;
    auto start = std::chrono::high_resolution_clock::now();

    std::thread threadArr[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; ++i)
    {
    	threadArr[i] = std::thread(&incrementManyTimes, std::ref(number));
    }

    for (int i = 0; i < MAX_THREAD; ++i)
    {
    	threadArr[i].join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Final number [" << number << "]" << std::endl;
    std::cout << "Operation took " << std::chrono::duration<double, std::milli>(end - start).count() << " milliseconds" << std::endl;
    return 0;
}
