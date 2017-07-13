#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "Level.hpp"
#include "libtcod.hpp"

class Item{
private:
  int x;
  int y;
  int character;
  TCODColor colour;
  std::string name;
public:
  std::string getName();
  void showAt(int x, int y);
  void show();
  void setPos(int x, int y);
  int getY();
  int getX();
  virtual void use(Creature* user, Level* level) = 0;
  Item(int character, TCODColor colour, std::string name);
};

#endif
