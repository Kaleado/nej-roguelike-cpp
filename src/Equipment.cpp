#include "libtcod.hpp"
#include "Equipment.hpp"

Equipment::Equipment(SlotType type, int character,
                     TCODColor color, std::string name,
                     int * stats)
  : Item(character, color, name) {
  this->type = type;

  // Make new array, copy over stats
  this->stats = new int[AMOUNT_ATTRIBUTE_TYPES];
  for (int i =0; i < AMOUNT_ATTRIBUTE_TYPES; i++){
    this->stats[i] = stats[i];
  }
}

int Equipment::getStat(AttributeType attr) {
  return this->stats[attr];
}
