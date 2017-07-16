#ifndef TARGETING_SYSTEM_HPP
#define TARGETING_SYSTEM_HPP

#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"

class TargetingSystem {
private:
  int cursorX, cursorY;
  bool isTargeting;
public:
  void setCursorPos(int nx, int ny);
  void getCursorPos(int* cx, int* cy);
  bool getIsTargeting();
  void startTargeting();
  void stillTargeting();
  void finishTargeting();
  TargetingSystem();
};

extern TargetingSystem* targetingSystem;

#endif
