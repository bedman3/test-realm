#include <iostream>
#include <thread>
#include <cstring>
#include <ctime>
#include <chrono>
#include <atomic>

#define EACH_THREAD_ITER 1e9
// #define MAX_THREAD 1

template <typename Integer>
void incrementManyTimes(Integer &number) {
    for (long long int i = 0; i < EACH_THREAD_ITER; ++i) {
        ++number;
    }
}

void case1() {
    long long int number = 0, MAX_THREAD = 3;
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Case 1 non atomic: MAX_THREAD [" << MAX_THREAD << "]" << std::endl;

    std::thread threadArr[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i] = std::thread(&incrementManyTimes<long long int>, std::ref(number));
    }

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i].join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Final number [" << number << "]" << std::endl;
    std::cout << "Operation took " << std::chrono::duration<double, std::milli>(end - start).count() << " milliseconds" << std::endl;
}

void case2() {
    long long int number = 0, MAX_THREAD = 1;
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Case 2 non atomic: MAX_THREAD [" << MAX_THREAD << "]" << std::endl;

    std::thread threadArr[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i] = std::thread(&incrementManyTimes<long long int>, std::ref(number));
    }

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i].join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Final number [" << number << "]" << std::endl;
    std::cout << "Operation took " << std::chrono::duration<double, std::milli>(end - start).count() << " milliseconds" << std::endl;
}

void case3() {
    std::atomic<long long int> number(0);
    int MAX_THREAD = 3;
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Case 3 atomic: MAX_THREAD [" << MAX_THREAD << "]" << std::endl;

    std::thread threadArr[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i] = std::thread(&incrementManyTimes<std::atomic<long long int>>, std::ref(number));
    }

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i].join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Final number [" << number << "]" << std::endl;
    std::cout << "Operation took " << std::chrono::duration<double, std::milli>(end - start).count() << " milliseconds" << std::endl;
}

void case4() {
    std::atomic<long long int> number(0);
    int MAX_THREAD = 1;
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Case 4 atomic: MAX_THREAD [" << MAX_THREAD << "]" << std::endl;

    std::thread threadArr[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i] = std::thread(&incrementManyTimes<std::atomic<long long int>>, std::ref(number));
    }

    for (int i = 0; i < MAX_THREAD; ++i) {
        threadArr[i].join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Final number [" << number << "]" << std::endl;
    std::cout << "Operation took " << std::chrono::duration<double, std::milli>(end - start).count() << " milliseconds" << std::endl;
}

int main() {
    std::cout << "EACH_THREAD_ITER [" << EACH_THREAD_ITER << "]" << std::endl;

    case1();
    case2();
    case3();
    case4();

    return 0;
}
