#include "libtcod.hpp"
#include "Level.hpp"
#include "Creature.hpp"
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



TileWrapper::TileWrapper(TileType* tile){
  this->tile = tile;
}

void TileWrapper::showAt(int x, int y){
  tile->showAt(x, y);
}


Level::Level(){
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      terrain[x][y] = NULL;
    }
  }
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
}

void Level::generate(){
  TileType* wall = new TileType('#', TCODColor::white, false);
  TileType* floor = new TileType('.', TCODColor::grey, true);
  for(int x = 0; x < LEVEL_WIDTH; x++){
    for(int y = 0; y < LEVEL_HEIGHT; y++){
      terrain[x][y] = new TileWrapper(floor);
    }
  }
}

void Level::addCreature(Creature* c){
  creatures.push_back(c);
}

void Level::removeCreature(Creature* c){
  creatures.erase(std::remove(creatures.begin(), creatures.end(), c), creatures.end());
}
