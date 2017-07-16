#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "libtcod.hpp"

//Does not activate any effect when targeting is finished - just for
//looking around.
#define TARGET_STYLE_LOOK 0
//Activates effect on the creature at the targeted point.
#define TARGET_STYLE_ON_CREATURE 1
//Activates effect on the map tile at the targeted point.
#define TARGET_STYLE_AT_POINT 2

class Creature;
class Level;

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
  virtual void use(Creature* user, Level* level);
  virtual void useOn(Creature* user, Creature* target, Level* level);
  virtual void useAtPoint(Creature* user, int x, int y, Level* level);
  Item(int character, TCODColor colour, std::string name);
};

#endif
