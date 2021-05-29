#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <string>
#include <iostream>
#include "word.h"
#include "DoubleLinkedList.hpp"

class HashTable
{
public:
  HashTable(size_t size);
  void insert(std::istream& in);
  void search(std::istream& in);
  void deleteWord(std::istream& in);
  void show(std::istream& in, std::ostream& out);
private:
  std::vector< DoubleLinkedList< Word > > array_;
  size_t tableSize_;
  int numOfCollsions_;
  int getHash(const std::string& englishWord);
};

#endif
