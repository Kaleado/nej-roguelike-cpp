#include "Item.hpp"

Item::Item(int character, TCODColor colour, std::string name){
  this->character = character;
  this->colour = colour;
  this->name = name;
}

void Item::use(Creature* user, Level* level) {
}

void Item::showAt(int x, int y){
  TCODConsole::root->setChar(x, y, character);
  TCODConsole::root->setCharForeground(x, y, colour);
}

void Item::show(){
  TCODConsole::root->setChar(x, y, character);
  TCODConsole::root->setCharForeground(x, y, colour);
}

void Item::setPos(int x, int y) {
  this->x = x;
  this->y = y;
}

int Item::getX() {
  return this->x;
}
int Item::getY() {
  return this->y;
}

std::string Item::getName(){
  return name;
}
