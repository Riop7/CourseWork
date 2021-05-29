#include "tools.h"
#include <locale>
#include <algorithm>

bool checkWordIsCorrect(const std::string& word)
{
  for (size_t i = 0; i < word.length(); i++)
  {
    std::locale locRu("ru-RU");
    std::locale locUS("en-US");
    if (!std::isalpha(word[i], locRu) && !std::isalpha(word[i], locUS) && !std::isspace(word[i]))
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
