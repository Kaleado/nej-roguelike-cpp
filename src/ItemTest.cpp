#include "ItemTest.hpp"

void ItemTest::use(Creature* user, Level* level){
  targetingSystem->startTargeting(TARGET_STYLE_AT_POINT, this);
  printf("asdf");
}

void ItemTest::useOn(Creature* user, Creature* target, Level* level){
}

void ItemTest::useAtPoint(Creature* user, int x, int y, Level* level){
  TileType* thingo = new TileType('_', TCODColor::green, true);
  level->setTileType(x, y, thingo);
}

ItemTest::ItemTest() : Item('&', TCODColor::blue, "Dummy item"){
}
