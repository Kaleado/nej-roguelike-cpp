#ifndef ITEM_TEST_HPP
#define ITEM_TEST_HPP

#include "libtcod.hpp"
#include "Level.hpp"
#include "TargetingSystem.hpp"
#include "Item.hpp"

class ItemTest : public Item {
private:
public:
  void use(Creature* user, Level* level);
  void useOn(Creature* user, Creature* target, Level* level);
  void useAtPoint(Creature* user, int x, int y, Level* level);
  ItemTest();
};

#endif
