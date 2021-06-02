#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include <vector>

bool checkRussianWordIsCorrect(const std::string& word);
bool checkEnglishWordIsCorrect(const std::string& word);
void mergeVectors(std::vector< std::string >& v1, std::vector< std::string >& v2);
void doStandartString(std::string& str);
void myToLower(std::string& str);

template < typename T >
void shakerSort(T* array, size_t size) {
  int left = 1,
    right = size - 1,
    i = 0;
  while (left <= right)
  {
    for (i = right; i >= left; i--)
    {
      if (array[i - 1] > array[i])
      {
        std::swap(array[i - 1], array[i]);
      }
    }
    left++;
    for (i = left; i <= right; i++)
    {
      if (array[i - 1] > array[i])
      {
        std::swap(array[i - 1], array[i]);
      }
    }
    right--;
  }
}

#endif