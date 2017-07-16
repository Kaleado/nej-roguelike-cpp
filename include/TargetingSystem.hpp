#ifndef TARGETING_SYSTEM_HPP
#define TARGETING_SYSTEM_HPP

#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"

class TargetingSystem {
private:
  Item* usingItem;
  int useStyle;
  int cursorX, cursorY;
  Creature* target;
  bool isTargeting;
public:
  void setCursorPos(int nx, int ny);
  void getCursorPos(int* cx, int* cy);
  Creature* getTarget();
  bool getIsTargeting();

  //Use this to enter targeting mode.
  void startTargeting(int useStyle, Item* usingItem);
  void stillTargeting();
  //Use this to exit targeting mode.
  void finishTargeting();
  
  TargetingSystem();
};

extern TargetingSystem* targetingSystem;

#endif
