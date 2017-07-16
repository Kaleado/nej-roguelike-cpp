#include "TargetingSystem.hpp"

void TargetingSystem::setCursorPos(int nx, int ny){
  cursorX = nx;
  cursorY = ny;
}

void TargetingSystem::getCursorPos(int* cx, int* cy){
  *cx = cursorX;
  *cy = cursorY;
}

bool TargetingSystem::getIsTargeting(){
  return isTargeting;
}

void TargetingSystem::startTargeting(){
  isTargeting = true;
  player->getPos(&cursorX, &cursorY);
}

void TargetingSystem::stillTargeting(){
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
  int playerx, playery;
  player->getPos(&playerx, &playery);
  bool movedCursor = false;
  switch(key.vk) {
  case TCODK_UP : cursorY--; movedCursor = true; break;
  case TCODK_DOWN : cursorY++; movedCursor = true; break;
  case TCODK_LEFT : cursorX--; movedCursor = true; break;
  case TCODK_RIGHT : cursorX++; movedCursor = true; break;
  case TCODK_ENTER : finishTargeting(); break;
  default : break;
  }
  Creature* underCursor = curLevel->creaturesAt(cursorX, cursorY);
  if(movedCursor && curLevel->isInFov(cursorX, cursorY) && underCursor){
    msgLog->pushMessage("Monster under cursor: " + underCursor->getName());
  }
  std::vector<Item*> onFloor = curLevel->itemsAt(cursorX, cursorY);
  if(movedCursor && curLevel->isInFov(cursorX, cursorY) && onFloor.size() > 0){
    std::string itemString = "";
    for(auto& it : onFloor){
      itemString += it->getName() + " ";
    }
    msgLog->pushMessage("Items under cursor: " + itemString);
  }
}

void TargetingSystem::finishTargeting(){
  isTargeting = false;
}

TargetingSystem::TargetingSystem() : isTargeting(false), cursorX(0), cursorY(0) {
}

TargetingSystem* targetingSystem = NULL;
