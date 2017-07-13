#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"
#include "Item.hpp" 
#include "CreatureDatabase.hpp"

Level* curLevel = NULL;
Creature* player = NULL;

int main() {
  player = new Creature('@', TCODColor::red);
  player->setPos(10, 10);
  curLevel = new Level();
  curLevel->generate();
  Creature* thing = new CreatureTest();
  curLevel->addCreature(player);
  curLevel->addCreature(thing);
  thing->setPos(15, 15);
  TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
  while ( !TCODConsole::isWindowClosed() ) {
    bool hasActed = false;
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
    int playerx, playery;
    player->getPos(&playerx, &playery);
    switch(key.vk) {
    case TCODK_UP : playery--; hasActed = true; break;
    case TCODK_DOWN : playery++; hasActed = true; break;
    case TCODK_LEFT : playerx--; hasActed = true; break;
    case TCODK_RIGHT : playerx++; hasActed = true; break;
    case TCODK_CHAR:
      if(key.c == 'g'){
	//Pickup
	player->pickup(curLevel);
	hasActed = true;
      }
      break;
    default:break;
    }
    if (curLevel->canMove(playerx, playery)) {
      player->setPos(playerx, playery);
    }
    if(hasActed){
      curLevel->takeTurns();
    }
    TCODConsole::root->clear();
    curLevel->show();
    TCODConsole::flush();
  }
  return 0;
}
