#include <iostream>
#include <string>
#include <fstream>

#include "DoubleLinkedList.hpp"
#include "word.h"
#include "hashTable.hpp"

int main()
{
  int code = 0;
  setlocale(LC_ALL, "RUS");
  system("chcp 1251");
  HashTable Dictionary(50);
  std::ifstream in("input.txt");

  int command = 1;
  try
  {
    //for (int i = 0; i < 5; i++)
    //{
    //  Dictionary.insert(in);
    //}
    std::cout << "Enter the command number\n"
      << "1 - insert the word in dictionary\n"
      << "2 - remove the word from dictionary\n"
      << "3 - show the translation\n"
      << "4 - find the word\n"
      << "0 - close the program\n";
    while (command)
    {
      if (!std::cin)
      {
        throw std::runtime_error("Invalid input\n");
      }
      std::cout << "Command number: ";
      std::cin >> command;
      std::cout << "\n";
      if (!std::cin)
      {
        throw std::invalid_argument("Invalid arguments\n");
      }
      if (command == 1)
      {
        std::cout << "Enter english word and translation like this\n\n";
        std::cout << "<english word>=<translation1>|<translation2>;\n";
        Dictionary.insert(std::cin);
      }
      else if (command == 2)
      {
        std::cout << "Enter english word for deletion\n";
        Dictionary.deleteWord(std::cin);
      }
      else if (command == 3)
      {
        std::cout << "Enter english word\n";
        Dictionary.show(std::cin);
      }
      else if (command == 4)
      {
        std::cout << "Enter english word\n";
        Dictionary.search(std::cin);
      }
      else if (command == 0)
      {
        code = 0;
      }
      else
      {
        throw std::invalid_argument("Wrong command number\n");
      }
    }
  }
  catch (const std::invalid_argument& exc)
  {
    std::cerr << exc.what();
    code = 1;
  }
  catch (const std::runtime_error& exc)
  {
    std::cerr << exc.what();
    code = 1;
  }
  return code;
}