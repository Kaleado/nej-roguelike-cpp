#ifndef MENU_HPP
#define MENU_HPP

#include "libtcod.hpp"
#include <string>
#include <vector>

class Menu{
protected:
  //TCODConsole colours
  TCODColor textColor;
  TCODColor backgroundColor;
  // Name of the panel - Menu, log, stats, etc.
  std::string name;
  // It's starting position on the screen
  int x, y;
  // Dimenions
  int width, height;
  // replaced top and content with a vector; top now useless
  std::vector<std::string> content;
  // Partition resizes an input string that is greater than the width of the menu.
  std::vector<std::string> partition(std::string input);
public:
  // Writes the menu to a TCODConsole screen
  virtual void drawMenu();
  // Sets a string in a given index. If the index is not provided, it is pushed
  // to the bottom of the menu.
  void setString(std::string message, int index=-1);
  void pushMessage(std::string str);
  void popMessage();
  void empty();
  Menu();
  Menu(int height, int width, int startx, int starty, std::string name,
       TCODColor text = TCODColor::white, TCODColor bg = TCODColor::black);
};

extern Menu* stats;
extern Menu* msgLog;

#endif
