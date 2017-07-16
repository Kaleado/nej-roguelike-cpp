#include "libtcod.hpp"
#include "Level.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include <cstdlib>
#include <string>
#include <ctime>
#include <algorithm>
#include <vector>

Level* curLevel = NULL;

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

void TileType::showHiddenAt(int x, int y){
  TCODConsole::root->setChar(x, y, character);
  TCODConsole::root->setCharBackground(x, y, TCODColor::black);
  TCODConsole::root->setCharForeground(x, y, TCODColor::grey);
}

void TileType::enter(){
  msgLog->pushMessage("You can't enter anything here.");
}

bool TileType::getIsPassable() {
  return this->isPassable;
}


TileWrapper::TileWrapper(TileType* tile){
  this->isExplored = false;
  this->tile = tile;
}

bool TileWrapper::getIsExplored(){
  return isExplored;
}

void TileWrapper::setIsExplored(bool v){
  isExplored = v;
}

TileType* TileWrapper::getTileType(){
  return this->tile;
}

void TileWrapper::setTileType(TileType* tileType){
  this->tile = tileType;
}

void TileWrapper::showAt(int x, int y){
  tile->showAt(x, y);
}

void TileWrapper::showHiddenAt(int x, int y){
  tile->showHiddenAt(x, y);
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
  map = new TCODMap(LEVEL_WIDTH, LEVEL_HEIGHT);
}

bool Level::isInFov(int x, int y) const {
  if(map->isInFov(x, y)){
    terrain[x][y]->setIsExplored(true);
    return true;
  }
  return false;
}

std::vector<Creature*> Level::getCreatures() {
  return this->creatures;
}

void Level::computeFov(){
  int px, py;
  player->getPos(&px, &py);
  map->computeFov(px, py, FOV_RADIUS);
}

std::vector<std::string> Level::takeTurns() {
  std::vector<std::string> log = std::vector<std::string>();
  for (auto &creat : creatures) {
    if (creat->isDead()){
      // Remove dead creature
      this->creatures.erase(
                            std::remove(this->creatures.begin(),
                                        this->creatures.end(),
                                        creat),
                            this->creatures.end());
      // Log that the creature died and delete it
      log.push_back(creat->getName() + " died!" );
    } else {
      log.push_back(creat->takeTurn(this));
    }
  }
  return log;
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
      TCODConsole::root->setCharBackground(x, y, TCODColor::black);
      //  TCODConsole::root->setCharForeground(x, y, charColor);
      if(isInFov(x, y)){
	terrain[x][y]->showAt(x, y);
      }
      else if(terrain[x][y]->getIsExplored()){
	terrain[x][y]->showHiddenAt(x, y);
      }
    }
  }
  for(auto &it : items){
    if(isInFov(it->getX(), it->getY())){
      it->show();
    }
  }  
  for(auto &creat : creatures){
    int cx, cy;
    creat->getPos(&cx, &cy);
    if(isInFov(cx, cy)){
      creat->show();
    }
  }
}

void Level::setTileType(int x, int y, TileType* tileType){
  this->terrain[x][y]->setTileType(tileType);
  this->map->setProperties(x, y, !tileType->getIsPassable(), !tileType->getIsPassable());
}

void Level::generate(){
  TileType* wall = new TileType('#', TCODColor::white, false);
  TileType* floor = new TileType('.', TCODColor::grey, true);
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      int num = rand() % 10;
      if (num < 3){
        terrain[x][y] = new TileWrapper(wall);
	this->map->setProperties(x, y, false, false);
      }
      else {
        if (num == 5) {
          Item* i = new Item('$', TCODColor::yellow, "ytb");
          i->setPos(x,y);
          this->items.push_back(i);
        }
        terrain[x][y] = new TileWrapper(floor);
	this->map->setProperties(x, y, true, true);
      }
    }
  }
}

void Level::enterAt(int x, int y){
  this->terrain[x][y]->getTileType()->enter();
  return;
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
