#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "libtcod.hpp"

class Creature {
private:
  int character;
  TCODColor colour;
  int x, y;
public:
  void pickUp();
  void showAt(int sx, int sy);
  void show();
  void getPos(int* rx, int* ry);
  void setPos(int nx, int ny);
  Creature(int character, TCODColor colour);
};

#endif
