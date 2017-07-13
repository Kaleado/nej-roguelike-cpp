#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "libtcod.hpp"

class Level;

class Creature {
private:
  int character;
  TCODColor colour;
  int x, y;
public:
  virtual void takeTurn(Level* lev);
  void showAt(int sx, int sy);
  void show();
  void getPos(int* rx, int* ry);
  void setPos(int nx, int ny);
  Creature(int character, TCODColor colour);
};

#endif
