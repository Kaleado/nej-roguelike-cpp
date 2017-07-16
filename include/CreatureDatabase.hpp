#ifndef CREATUREDATABASE_HPP
#define CREATUREDATABASE_HPP

#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"

class CreatureTest : public Creature{
public:
  std::string takeTurn(Level* lev);
  CreatureTest();
};

#endif
