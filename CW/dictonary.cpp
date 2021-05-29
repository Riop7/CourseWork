#include "dictionary.hpp"
#include <string>

#include "word.h"
#include "tools.h"

inline int Dictionary::getHash(const std::string& englishWord)
{
  int hash = 0;
  for (size_t i = 0; i < englishWord.length(); i++)
  {
    hash += englishWord[i];
  }
  hash = hash % tableSize_;
  return hash;
}

Dictionary::Dictionary(size_t size):
  tableSize_(size),
  numOfCollsions_(0)
{
  for (int i = 0; i < size; i++)
  {
    array_.push_back(DoubleLinkedList< Word >());
  }
}

void Dictionary::insert(std::istream& in)
{
  Word word;
  word.insertWord(in);
  int index = getHash(word.getEnglishWord());
  if (!array_[index].empty())
  {
    if (array_[index].searchItem(word))
    {
      mergeVectors(array_[index].searchItem(word)->item_.getVect(), word.getVect());
    }
    else
    {
      numOfCollsions_++;
      array_[index].insertHead(word);
    }
  }
  else
  {
    array_[index].insertHead(word);
  }
}

void Dictionary::search(std::istream& in, std::ostream& out)
{
  std::string englishWord;
  do
  {
    getline(in, englishWord);
  } while (englishWord.empty());
  if (!in)
  {
    return;
  }
  Word engWord(englishWord);
  int index = getHash(englishWord);
  
  if (array_[index].searchItem(engWord))// O(n)
  {
    std::cout << "Dictionary contains this word\n";
  }
  else
  {
    std::cout << "Dictionary does not contain this word\n";
  }
}

void Dictionary::deleteWord(std::istream& in)
{
  std::string englishWord;
  do
  {
    getline(in, englishWord);
  } while (!in.eof() && englishWord.empty());
  int index = getHash(englishWord);
  Word engWord(englishWord);
 
  if (array_[index].searchItem(engWord))
  {
    array_[index].searchItem(engWord)->item_.clear();
  }
  else
  {
    throw std::runtime_error("Dictionary does not contains this word\n");
  }
}

void Dictionary::show(std::istream& in, std::ostream& out)
{
  std::string englishWord;
  do 
  {
    getline(in, englishWord);
  } while (!in.eof() && englishWord.empty());
  Word engWord(englishWord);
  int index = getHash(englishWord);
  if (array_[index].searchItem(engWord))
  {
    array_[index].searchItem(engWord)->item_.show(out);
    out << "\n";
  }
  else
  {
    throw std::runtime_error("Dictionary does not contain this word\n");
  }
}
