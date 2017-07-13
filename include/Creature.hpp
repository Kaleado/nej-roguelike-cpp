#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "libtcod.hpp"
#include <vector>

class Level;
class Item;

class Creature {
private:
  int strength, dexterity, constitution, intelligence, wisdom, charisma;
  int hp, maxHp;
  int character;
  TCODColor colour;
  int x, y;
  std::vector<Item*> inventory;
public:
  virtual void takeTurn(Level* lev);
  void pickup(Level* lev);
  void showAt(int sx, int sy);
  void show();
  void getPos(int* rx, int* ry);
  void setPos(int nx, int ny);
  Creature();
  Creature(int character, TCODColor colour);
};

#endif
