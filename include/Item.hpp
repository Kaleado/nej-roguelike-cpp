#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "Level.hpp"
#include "libtcod.hpp"

class Item{
private:
  int character;
  TCODColor colour;
  std::string name;
public:
  std::string getName();
  void showAt(int x, int y);
  virtual void use(Creature* user, Level* level) = 0;
  Item(int character, TCODColor colour, std::string name);
};

#endif
