#include "Item.hpp"
#include "Equipment.hpp"
#include <random>
#include <ctime>

Item::Item(int character, TCODColor colour, std::string name){
  this->character = character;
  this->colour = colour;
  this->name = name;
}

Item* Item::generateRandomItem() {
  srand(time(NULL));
  int type = (rand() % 2*AMOUNT_EQUIPMENT_TYPES);

  Item * it = NULL;

  // 50% chance of being a piece of equipment
  if (type < AMOUNT_EQUIPMENT_TYPES) {
    int statArr[AMOUNT_ATTRIBUTE_TYPES] = {0};
    it = (Item*) new Equipment((SlotType)type, '+', TCODColor::pink,
                               "Mystery Equipment", statArr);
  } else {
    it = new Item('$', TCODColor::yellow, "GenericItem");
  }

  return it;
}

void Item::use(Creature* user, Level* level) {
}

void Item::useOn(Creature* user, Creature* target, Level* level) {
}

void Item::useAtPoint(Creature* user, int x, int y, Level* level) {
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
