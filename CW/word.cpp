#include "word.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "tools.h"

Word::Word():
  englishWord_("<EMPTY>")
{
}

Word::Word(std::string englishWord):
  englishWord_(englishWord)
{
}

void Word::insertWord(std::istream& in)
{
  std::string line;
  do
  {
    getline(in, line);
  } while (line.empty() && !in.eof());
  if (line.empty() && !in.eof())
  {
    throw std::invalid_argument("Empty input");
  }
  std::stringstream sin(line);
  char current = sin.get();
  englishWord_.clear();
  sin >> std::ws;
  while (current != '=' && !sin.fail())
  {
    englishWord_ += current;
    current = sin.get();
  } 
  if (englishWord_.empty() || current != '=')
  {
    throw std::invalid_argument("Invalid input\n");
  }
  myToLower(englishWord_);
  doStandartString(englishWord_);
  if (!checkWordIsCorrect(englishWord_))
  {
    throw std::invalid_argument("Invalid english word\n");
  }

  bool flag = true;
  while (flag)
  {
    std::string translation;
    sin >> std::ws;
    current = sin.get();
    while (!sin.fail() && current != '|')
    {
      translation += current;
      current = sin.get();
    }
    if (translation.empty())
    {
      throw std::invalid_argument("Invalid input\n");
    }
    if (sin.eof())
    {
      flag = false;
    }
    doStandartString(translation);
    myToLower(translation);
    if (!checkWordIsCorrect(translation))
    {
      throw std::invalid_argument("Invalid translation\n");
    }
    translations_.push_back(translation);
  }
  std::sort(translations_.begin(), translations_.end());
}

std::string Word::getEnglishWord()
{
  return englishWord_;
}

std::vector<std::string>& Word::getVect()
{
  return translations_;
}

void Word::show(std::ostream& out)
{
  std::copy(translations_.begin(), translations_.end(), std::ostream_iterator< std::string >(out, " "));
}

void Word::clear()
{
  englishWord_.clear();
  translations_.clear();
}

bool Word::operator==(const Word& rhs)
{
  return englishWord_ == rhs.englishWord_;
}

bool Word::operator!=(const Word& rhs)
{
  return englishWord_ != rhs.englishWord_;
}
