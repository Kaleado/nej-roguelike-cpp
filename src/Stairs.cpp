#include "Stairs.hpp"

void TileTypeStairs::enter(){
  curLevel->removeCreature(player);
  curLevel = this->destinationLevel;
  curLevel->addCreature(player);
  player->setPos(this->destinationX, this->destinationY);
  msgLog->pushMessage("You walk down the stairs.");
  curLevel->computeFov();
}

TileTypeStairs::TileTypeStairs(int character,
			       TCODColor charColor,
			       bool passable,
			       TCODColor bgColor, Level* dest, int dx, int dy)
  : TileType(character, charColor, passable, bgColor){
  this->destinationLevel = dest;
  this->destinationX = dx;
  this->destinationY = dy;
}
