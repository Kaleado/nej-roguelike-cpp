#ifndef MENU_HPP
#define LEVEL_HPP

#include "libtcod.hpp"
#include <string>

class Menu{
private:
  std::string name;
  int x, y;
  int width, height;
  // These two are the strings to print and
  // The current amount of strings filling the array
  std::string * content;
  int top;
public:
  void drawMenu();
  void setString(std::string message, int index=-1);
  Menu(int height, int width, int startx, int starty, std::string name);
};

#endif
