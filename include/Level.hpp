#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "libtcod.hpp"
#include "Creature.hpp"
#include <vector>

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 100

//The actual type of tile, e.g. wall, floor, etc.
class TileType{
private:
  bool isPassable;
  int character;
  TCODColor colour;
public:
  void showAt(int x, int y);
  TileType(int character, TCODColor colour, bool passable);
};

//This class exists so that we can encapsulate things specific only to
//particular tiles, e.g. if tiles are on fire, etc.
class TileWrapper{
private:
  TileType* tile;
public:
  void showAt(int x, int y);
  TileWrapper(TileType* tile);
};

class Level{
private:
  TileWrapper* terrain[LEVEL_WIDTH][LEVEL_HEIGHT];
  std::vector<Creature*> creatures;
public:
  void show();
  virtual void generate();
  void addCreature(Creature* c);
  Level();
};

#endif
