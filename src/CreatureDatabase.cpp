#include "CreatureDatabase.hpp"

std::string CreatureTest::takeTurn(Level* lev){
  int dx = (rand() % 3) - 1;
  int dy = (rand() % 3) - 1;
  int charx, chary;
  getPos(&charx, &chary);
  if (lev->canMove(charx+dx, chary+dy) && dx != 0 && dy != 0){
    return move(charx+dx, chary+dy, lev);
  }
  return "";
}

CreatureTest::CreatureTest() : Creature('$', TCODColor::green, "Monster") {
}
