#include "tools.hpp"
#include <locale>
#include <algorithm>

bool checkRussianWordIsCorrect(const std::string& word)
{
  for (size_t i = 0; i < word.length(); i++)
  {
    if ((word[i] < 'à' || word[i] > 'ÿ') && !std::isspace(word[i]))
    {
      return false;
    }
  }
  return true;
}

bool checkEnglishWordIsCorrect(const std::string& word)
{
  for (size_t i = 0; i < word.length(); i++)
  {
    if (!std::isalpha(word[i]) && !std::isspace(word[i]))
    {
      return false;
    }
  }
  return true;
}

void mergeVectors(std::vector<std::string>& v1, std::vector<std::string>& v2)
{
  v1.insert(v1.end(), v2.begin(), v2.end());
  std::sort(v1.begin(), v1.end());
  v1.erase(std::unique(v1.begin(), v1.end()), v1.end());
}

void doStandartString(std::string& str)
{
  while (str.back() == ' ')
  {
    str.pop_back();
  }
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
