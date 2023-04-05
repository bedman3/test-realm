
#include <iostream>
#include <vector>

std::vector<int> mergeSort(std::vector<int>& vec, int start, int end) {
    if (end < start)
        return std::vector<int>();
    else if (end == start)
        return vec;

    int mid = (vec.size() - 1) / 2;
    std::vector<int> arr1 = mergeSort(vec, start, mid - 1), arr2 = mergeSort(vec, mid, end);
}

void printVec(std::vector<int>& vec) {
    bool firstNum = true;
    std::cout << "Printing vector [";
    for (int i = 0; i < vec.size(); ++i) {
        int num = vec[i];
        if (firstNum) {
            firstNum = false;
            std::cout << num;
        } else {
            std::cout << ", " << num;
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    const int NUM_ELEMENTS = 100;
    std::vector<int> array1;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        array1.push_back(rand() % NUM_ELEMENTS);
    }
    std::cout << "Init vector" << std::endl;
    printVec(array1);

    array1 = mergeSort(array1, 0, array1.size() - 1);
}