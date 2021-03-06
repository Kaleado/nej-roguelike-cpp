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
  virtual std::string takeTurn(Level* lev);
  void pickup(Level* lev);
  void showAt(int sx, int sy);
  void show();
  int getHp();
  int getMaxHp();
  std::string getName();
  bool isDead();
  void getPos(int* rx, int* ry);
  void setPos(int nx, int ny);
  std::vector<Item*> getInventory();
  std::string move(int nx, int ny, Level* lvl);
  std::string attack(int x, int y, Creature* enemy);
  Creature();
  Creature(int character, TCODColor colour, std::string name,
           int str = 10, int dex = 10,
           int con  = 10, int intel = 10, int wis = 10, int cha = 10,
           int maxHP = 20);
};

extern Creature* player;

#endif
