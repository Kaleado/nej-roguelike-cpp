#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "libtcod.hpp"

#define AMOUNT_ATTRIBUTE_TYPES 6
enum AttributeType {STRENGTH,DEXTERITY,CONSTITUTION,INTELLIGENCE,WISDOM,CHARISMA};

class Creature;
class Level;

class Item{
protected:
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
  virtual void use(Creature* user, Level* level);
  Item(int character, TCODColor colour, std::string name);
};

#endif
