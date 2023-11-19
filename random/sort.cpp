
#include <iostream>
#include <ostream>
#include <vector>

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
    std::cout << "Test cpp" << std::endl;
    std::cout << "]" << std::endl;
}

std::vector<int> mergeVec(std::vector<int> arr1, std::vector<int> arr2) {
    std::vector<int> returnVec;
    int i = 0, j = 0;
    while (i < arr1.size() || j < arr2.size()) {
        if (j < arr2.size() && (i == arr1.size() || arr1[i] > arr2[j]))
            returnVec.push_back(arr2[j++]);
        else
            returnVec.push_back(arr1[i++]);
    }
    return returnVec;
}

std::vector<int> mergeSort(std::vector<int>& vec, int start, int end) {
    if (end <= start)
        return {vec[start]};
    else if (end - start == 1)
        if (vec[start] > vec[end])
            return {vec[end], vec[start]};
        else
            return {vec[start], vec[end]};

    int mid = (end + start) / 2;
    return mergeVec(mergeSort(vec, start, mid), mergeSort(vec, mid + 1, end));
}

int main() {
    const int NUM_ELEMENTS = 10;
    std::vector<int> array1;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        array1.push_back(rand() % NUM_ELEMENTS);
    }
    std::cout << "Init vector" << std::endl;
    printVec(array1);

    array1 = mergeSort(array1, 0, array1.size() - 1);
    std::cout << "Finish sorting" << std::endl;
    printVec(array1);
}
