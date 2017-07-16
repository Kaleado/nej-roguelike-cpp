#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "libtcod.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include <vector>

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 50

//The actual type of tile, e.g. wall, floor, etc.
class TileType{
private:
  bool isPassable;
  int character;
  TCODColor charColor;
  TCODColor bgColor;
public:
  bool getIsPassable();
  void showAt(int x, int y);
  TileType(int character, TCODColor colour, bool passable,
           TCODColor bgColor = TCODColor::black);
};

//This class exists so that we can encapsulate things specific only to
//particular tiles, e.g. if tiles are on fire, etc.
class TileWrapper{
private:
  TileType* tile;
public:
  bool isPassable();
  void showAt(int x, int y);
  TileWrapper(TileType* tile);
};

class Level{
private:
  TileWrapper* terrain[LEVEL_WIDTH][LEVEL_HEIGHT];
  std::vector<Creature*> creatures;
  std::vector<Item*> items;
public:
  std::vector<Item*> itemsAt(int x, int y);
  Creature* creaturesAt(int x, int y);
  std::vector<std::string> takeTurns();
  Item* itemAt(int x, int y);
  bool canMove(int x, int y);
  void show();
  virtual void generate();
  void addCreature(Creature* c);
  void removeCreature(Creature* c);
  void removeItem(Item* it);
  Level();
};

#endif
