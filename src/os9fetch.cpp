#include "stdio.h"
#include <functional>
#include "logo.hpp"

#include "detection/functions.hpp"
#include "console/Console.hpp"
#include "console/ConsoleWindow.hpp"

void main_below_4();
void main_above_4();

int main()
{
  retro::InitConsole();

  auto functions = detection::functions();
  std::vector<std::string> buf = std::vector<std::string>();

  for (int i = 0; i < apple_logo.size(); i++)
  {
    auto logo = apple_logo[i].c_str();
    printf("%s ", logo);
    if (i < functions.size())
    {
      functions[i]();
    }
    printf("\n");
  }

  retro::Console::currentInstance->ReadLine();
  return 0;
}

void main_below_4()
{
  retro::InitConsole();

  for (int i = 0; i < apple_logo.size(); i++)
  {
    auto logo = apple_logo[i];

    retro::Console::currentInstance->write(logo.c_str(), logo.size());
    retro::Console::currentInstance->write("\n", 1);
  }

  retro::Console::currentInstance->ReadLine();
}

void main_above_4()
{
  retro::InitConsole();

  auto functions = detection::functions();
  std::vector<std::string> buf = std::vector<std::string>();

  for (int i = 0; i < apple_logo.size(); i++)
  {
    auto logo = apple_logo[i].c_str();
    printf("%s ", logo);
    if (i < functions.size())
    {
      functions[i]();
    }
    printf("\n");
  }

  retro::Console::currentInstance->ReadLine();
}