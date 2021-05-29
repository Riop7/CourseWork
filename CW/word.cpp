#include "word.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
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
  } while (line.empty());
  std::stringstream sin(line);
  char my_or = '\0';
  char semicolon = '\0';
  char current = sin.get();
  englishWord_.clear();
  sin >> std::ws;
  while (current != '=' && !sin.fail())
  {
    englishWord_ += current;
    current = sin.get();
  } 
  if (current != '=')
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
    while ((current != '|' && current != ';') && !sin.fail())
    {
      translation += current;
      current = sin.get();
    }
    if (translation.empty() || (sin.fail() && current != ';'))
    {
      throw std::invalid_argument("Invalid translation\n");
    }
    if (current == ';')
    {
      flag = false;
    }
    //sin >> translation;
    doStandartString(translation);
    if (translation.empty())
    {
      throw std::invalid_argument("Invalid translation\n");
    }
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

void myToLower(std::string& str)
{
  for (size_t i = 0; i < str.length(); i++)
  {
    if (str[i] >= 'A' && str[i] <= 'Z')
    {
      str[i] += 'z' - 'Z';
    }
    if (str[i] >= 'À' && str[i] <= 'ß')
    {
      str[i] += 'ÿ' - 'ß';
    }
  }
}
