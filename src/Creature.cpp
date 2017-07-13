#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"
#include "Item.hpp"

void Creature::setPos(int nx, int ny){
  this->x = nx;
  this->y = ny;
}

void Creature::getPos(int* rx, int* ry){
    *rx = this->x;
    *ry = this->y;
}

void Creature::addItemToInventory(Item* i) {
  this->inventory.push_back(i);
}

void Creature::showAt(int sx, int sy){
  TCODConsole::root->setChar(sx, sy, character);
  TCODConsole::root->setCharForeground(sx, sy, colour);
}

void Creature::show(){
  showAt(x, y);
}

void Creature::takeTurn(Level* lev){
  return;
}

Creature::Creature(){
}

Creature::Creature(int character, TCODColor colour){
  this->colour = colour;
  this->character = character;
}
