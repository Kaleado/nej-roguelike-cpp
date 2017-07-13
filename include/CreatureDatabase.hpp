#ifndef CREATUREDATABASE_HPP
#define CREATUREDATABASE_HPP

#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"

class CreatureTest : public Creature{
public:
  void takeTurn(Level* lev);
  CreatureTest();
};

#endif
