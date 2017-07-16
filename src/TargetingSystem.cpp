#include "TargetingSystem.hpp"

void TargetingSystem::setCursorPos(int nx, int ny){
  cursorX = nx;
  cursorY = ny;
}

void TargetingSystem::getCursorPos(int* cx, int* cy){
  *cx = cursorX;
  *cy = cursorY;
}

Creature* TargetingSystem::getTarget(){
  return target;
}

bool TargetingSystem::getIsTargeting(){
  return isTargeting;
}

void TargetingSystem::startTargeting(int useStyle, Item* usingItem){
  this->useStyle = useStyle;
  this->usingItem = usingItem;
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
  target = curLevel->creaturesAt(cursorX, cursorY);
  if(!curLevel->isInFov(cursorX, cursorY)){
    target = NULL;
    usingItem = NULL;
    return;
  }
  if(usingItem && useStyle != TARGET_STYLE_LOOK){
    if(target && useStyle == TARGET_STYLE_ON_CREATURE){
      usingItem->useOn(player, target, curLevel);
    }
    else if(useStyle == TARGET_STYLE_AT_POINT){
      usingItem->useAtPoint(player, cursorX, cursorY, curLevel);
    }
  }
  usingItem = NULL;
}

TargetingSystem::TargetingSystem() : isTargeting(false), cursorX(0), cursorY(0), usingItem(NULL), target(NULL) {
}

TargetingSystem* targetingSystem = NULL;
