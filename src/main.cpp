#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"
#include "Item.hpp" 

Level* curLevel = NULL;
Creature* player = NULL;

int main() {
  player = new Creature('@', TCODColor::red);
  player->setPos(10, 10);
  curLevel = new Level();
  curLevel->generate();
  curLevel->addCreature(player);
  TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
  while ( !TCODConsole::isWindowClosed() ) {
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
    int playerx, playery;
    player->getPos(&playerx, &playery);
    switch(key.vk) {
    case TCODK_UP : playery--; break;
    case TCODK_DOWN : playery++; break;
    case TCODK_LEFT : playerx--; break;
    case TCODK_RIGHT : playerx++; break;
    default:break;
    }
    if (curLevel->canMove(playerx, playery)) {
      player->setPos(playerx, playery);
      player->pickup(curLevel);
    }
    TCODConsole::root->clear();
    curLevel->show();
    TCODConsole::flush();
  }
  return 0;
}
