#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include "libtcod.hpp"
#include "Item.hpp"
#include <string>

#define AMOUNT_EQUIPMENT_TYPES 6
enum SlotType {HAT,NECK,ARMOUR,RING,BOOTS,WEAPON};

class Equipment : public Item {
private:
  SlotType type;
  int * stats;
public:
  int getStat(AttributeType attr);
  Equipment(SlotType type, int character, TCODColor color,
            std::string name, int* stats);
};

#endif
