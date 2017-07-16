#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "libtcod.hpp"
#include <string>
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
  std::string name;
  // Functions
  void hpDelta(int dmg);
public:
  virtual void takeTurn(Level* lev);
  void pickup(Level* lev);
  void showAt(int sx, int sy);
  void show();
  void getPos(int* rx, int* ry);
  void setPos(int nx, int ny);
  std::string move(int nx, int ny, Level* lvl);
  std::string attack(int x, int y, Creature* enemy);
  Creature();
  Creature(int character, TCODColor colour, std::string name,
           int str = 5, int dex = 5,
           int con  = 5, int intel = 5, int wis = 5, int cha = 5,
           int maxHP = 10);
};

#endif
