#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "libtcod.hpp"
#include <vector>

class Level;
class Item;

class Creature {
private:
  int character;
  TCODColor colour;
  int x, y;
  std::vector<Item*> inventory;
public:
  virtual void takeTurn(Level* lev);
  void addItemToInventory(Item* i);
  void showAt(int sx, int sy);
  void show();
  void getPos(int* rx, int* ry);
  void setPos(int nx, int ny);
  Creature(int character, TCODColor colour);
};

#endif
