#include "libtcod.hpp"
#include "Level.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

TileType::TileType(int character, TCODColor colour, bool passable){
  this->character = character;
  this->colour = colour;
  this->isPassable = passable;
}

void TileType::showAt(int x, int y){
  TCODConsole::root->setChar(x, y, character);
  TCODConsole::root->setCharForeground(x, y, colour);
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

Item * Level::itemAt(int x, int y) {
  if (!(x < LEVEL_WIDTH) || !(y < LEVEL_HEIGHT))
    return NULL;

  for (auto &it : items) {
    if (it->getX() == x && it->getY() == y)
      return it;
  }

  return NULL;
}

void Level::show(){
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      terrain[x][y]->showAt(x, y);
    }
  }
  for(auto &creat : creatures){
    creat->show();
  }

  for(auto &it : items){
    it->show();
  }
}

void Level::generate(){
  srand(time(NULL));
  TileType* wall = new TileType('#', TCODColor::white, false);
  TileType* floor = new TileType('.', TCODColor::grey, true);
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      int num = rand() % 3;
      if (num == 0)
        terrain[x][y] = new TileWrapper(wall);
      else
        terrain[x][y] = new TileWrapper(floor);
    }
  }
}

void Level::addCreature(Creature* c){
  creatures.push_back(c);
}

bool Level::canMove(int x, int y) {
  if (!(x < LEVEL_WIDTH) || !(y < LEVEL_HEIGHT))
    return false;
  if (! terrain[x][y]->isPassable())
    return false;
  return true;
}

void Level::removeCreature(Creature* c){
  creatures.erase(std::remove(creatures.begin(), creatures.end(), c), creatures.end());
}
