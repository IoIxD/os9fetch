#include "stdio.h"
#include <string>
#include <vector>
#include <functional>

std::vector<std::string> apple_logo = {"                    'c.              ",
                                       "                 ,xNMM.              ",
                                       "               .OMMMMo               ",
                                       "               OMMM0,                ",
                                       "     .;loddo:' loolloddol;.          ",
                                       "   cKMMMMMMMMMMNWMMMMMMMMMM0:        ",
                                       " .KMMMMMMMMMMMMMMMMMMMMMMMWd.        ",
                                       " XMMMMMMMMMMMMMMMMMMMMMMMX.          ",
                                       ";MMMMMMMMMMMMMMMMMMMMMMMM:           ",
                                       ":MMMMMMMMMMMMMMMMMMMMMMMM:           ",
                                       ".MMMMMMMMMMMMMMMMMMMMMMMMX.          ",
                                       " kMMMMMMMMMMMMMMMMMMMMMMMMWd.        ",
                                       " .XMMMMMMMMMMMMMMMMMMMMMMMMMMk       ",
                                       "  .XMMMMMMMMMMMMMMMMMMMMMMMMK.       ",
                                       "    kMMMMMMMMMMMMMMMMMMMMMMd         ",
                                       "     ;KMMMMMMMWXXWMMMMMMMk.          ",
                                       "       .cooc,.    .,coo:.            "};

#include "detection/functions.hpp"

int main()
{
  auto functions = detection::functions();
  std::vector<std::string> buf = std::vector<std::string>();

  for (int i = 0; i < apple_logo.size(); i++)
  {
    printf("%s ", apple_logo[i].c_str());
    if (i < functions.size())
    {
      functions[i]();
    }
    printf("\n");
  }

  getchar();
  return 0;
}
