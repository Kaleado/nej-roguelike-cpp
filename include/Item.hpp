#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "libtcod.hpp"

class Item{
private:
  int character;
  TCODColor colour;
  std::string name;
public:
  std::string getName();
  void showAt(int x, int y);
  Item(int character, TCODColor colour, std::string name);
};

#endif
