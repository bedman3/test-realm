#include <iostream>
#include <vector>

std::vector<int> mergeSort(const std::vector<int>& arr, int start, int end) {
  if (start == end) {
    std::vector<int> returnArr;
    returnArr.push_back(arr[start]);
    return returnArr;
  }
  
  int median = (start + end) / 2;
  std::vector<int> list1 = mergeSort(arr, start, median);
  std::vector<int> list2 = mergeSort(arr, median + 1, end);
  std::vector<int> result;
  int i1, i2, list1Size, list2Size;
  list1Size = list1.size();
  list2Size = list2.size();
  
  i1 = i2 = 0;
  while (i1 < list1Size || i2 < list2Size) {
    if (i1 >= list1Size) {
      result.push_back(list2[i2++]);
    } else if (i2 >= list2Size) {
      result.push_back(list1[i1++]);
    } else if (list1[i1] < list2[i2]) {
      result.push_back(list1[i1++]); 
    } else {
      result.push_back(list2[i2++]);
    }
  }
  
  std::cout << "result:";
  for (auto i : result) {
    std::cout << " " << i;
  }
  std::cout << std::endl;
  
  return result;
}


int main() {
  
  // std::vector<int> testArr = {1, 5, 4, 3, 2, 6}, trueArr = {1, 2, 3, 4, 5, 6};
  std::vector<int> testArr = {1, 5, 4, 3, 2};
  std::vector<int> trueArr = {1, 2, 3, 4, 5};
  
  int arrSize = testArr.size();
  auto sortedArr = mergeSort(testArr, 0, arrSize);
  std::cout << "testArr:";
  for (auto i : testArr) {
    std::cout << " " << i;
  }
  std::cout << std::endl;
  
  std::cout << "sortedArr:";
  for (auto i : sortedArr) {
    std::cout << " " << i;
  }
  std::cout << std::endl;
  
  
  // test part
  if (sortedArr.size() != trueArr.size()) {
    std::cout << "Wrong size, true size: " << trueArr.size() << " sort size: " << sortedArr.size() << std::endl;
  } else {
     for (int i = 0; i < sortedArr.size(); ++i) {
        if (sortedArr[i] != trueArr[i]) {
          std::cout << "Wrong result at " << i << std::endl; 
        }
     }
  }
  
  return 0; 
}
