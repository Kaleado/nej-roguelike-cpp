#include "libtcod.hpp"
#include "Level.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

TileType::TileType(int character, TCODColor charColor, bool passable,
                   TCODColor bgColor){
  this->character = character;
  this->isPassable = passable;
  this->charColor = charColor;
  this->bgColor = bgColor;
}

void TileType::showAt(int x, int y){
  TCODConsole::root->setChar(x, y, character);
  TCODConsole::root->setCharBackground(x, y, bgColor);
  TCODConsole::root->setCharForeground(x, y, charColor);
}

bool TileType::getIsPassable() {
  return this->isPassable;
}


TileWrapper::TileWrapper(TileType* tile){
  this->tile = tile;
}

void TileWrapper::showAt(int x, int y){
  tile->showAt(x, y);
}

bool TileWrapper::isPassable() {
  return this->tile->getIsPassable();
}

Level::Level(){
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      terrain[x][y] = NULL;
    }
  }
}

void Level::takeTurns(){
  for (auto &creat : creatures) {
    creat->takeTurn(this);
  }
}

std::vector<Item*> Level::itemsAt(int x, int y) {
  std::vector<Item*> itemsFound;
  if (!(x < LEVEL_WIDTH) || !(y < LEVEL_HEIGHT))
    return itemsFound;

  for (auto &it : items) {
    if (it->getX() == x && it->getY() == y)
      itemsFound.push_back(it);
  } 

  return itemsFound;
}

Creature* Level::creaturesAt(int x, int y) {
  // Escape if out of bounds
  if (!(x < LEVEL_WIDTH) || !(y < LEVEL_HEIGHT))
    return NULL;
  if ((x < 0) || (y < 0))
    return NULL;

  for (auto &cre : creatures){
    int rx;
    int ry;
    cre->getPos(&rx,&ry);
    if (rx == x && ry == y)
      return cre;
  }

  return NULL;
}

void Level::show(){
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      terrain[x][y]->showAt(x, y);
    }
  }
  for(auto &it : items){
    it->show();
  }  
  for(auto &creat : creatures){
    creat->show();
  }
}

void Level::generate(){
  srand(time(NULL));
  TileType* wall = new TileType('#', TCODColor::white, false);
  TileType* floor = new TileType('.', TCODColor::grey, true);
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      int num = rand() % 10;
      if (num < 3)
        terrain[x][y] = new TileWrapper(wall);
      else {
        if (num == 5) {
          Item* i = new Item('$', TCODColor::yellow, "ytb");
          i->setPos(x,y);
          this->items.push_back(i);
        }
        terrain[x][y] = new TileWrapper(floor);
      }
    }
  }
}

Item* Level::itemAt(int x, int y){
  for(auto& it : items){
    if(it->getX() == x && it->getY() == y){
      return it;
    }
  }
  return NULL;
}

void Level::addCreature(Creature* c){
  creatures.push_back(c);
}

bool Level::canMove(int x, int y) {
  if (!(x < LEVEL_WIDTH) || !(y < LEVEL_HEIGHT) || y < 0 || x < 0)
    return false;
  if (! terrain[x][y]->isPassable())
    return false;
  return true;
}

void Level::removeCreature(Creature* c){
  creatures.erase(std::remove(creatures.begin(), creatures.end(), c), creatures.end());
}

void Level::removeItem(Item* it) {
  items.erase(std::remove(items.begin(), items.end(), it), items.end());
}
