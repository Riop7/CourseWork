#ifndef WORD_H
#define WORD_H

#include <vector>
#include <iostream>
#include "DoubleLinkedList.hpp"

class Word
{
public:
  Word();
  Word(std::string englishWord);
  void insertWord(std::istream& in);
  std::string getEnglishWord();
  std::vector< std::string >& getVect();
  void show();
  void clear();
  bool operator==(const Word& rhs);
  bool operator!=(const Word& rhs);
private:
  std::string englishWord_;
  std::vector< std::string > translations_;
};
void myToLower(std::string& str);

#endif

