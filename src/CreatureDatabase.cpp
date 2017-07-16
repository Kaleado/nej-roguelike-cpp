#include "CreatureDatabase.hpp"

void CreatureTest::takeTurn(Level* lev){
  int dx = (rand() % 3) - 1;
  int dy = (rand() % 3) - 1;
  int charx, chary;
  getPos(&charx, &chary);
  if (lev->canMove(charx+dx, chary+dy)){
    setPos(charx+dx, chary+dy);
  }
}

CreatureTest::CreatureTest() : Creature('$', TCODColor::green, "Monster") {
}
