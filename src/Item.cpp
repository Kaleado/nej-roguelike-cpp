#include "Item.hpp"

Item::Item(int character, TCODColor colour, std::string name){
  this->character = character;
  this->colour = colour;
}

void Item::showAt(int x, int y){
  TCODConsole::root->setChar(x, y, character);
  TCODConsole::root->setCharForeground(x, y, colour);
}

std::string Item::getName(){
  return name;
}
