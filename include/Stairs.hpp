#ifndef STAIRS_HPP
#define STAIRS_HPP

#include "Level.hpp"
#include "Creature.hpp"

class TileTypeStairs : public TileType{
private:
  Level* destinationLevel;
  int destinationX, destinationY;
public:
  void enter();
  TileTypeStairs(int character,
		 TCODColor charColor,
		 bool passable,
		 TCODColor bgColor, Level* dest, int dx, int dy);
    
};

#endif
