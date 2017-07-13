#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"
#include "Item.hpp"
#include "Menu.hpp"
#include "CreatureDatabase.hpp"

#define WINDOW_WIDTH 120
#define WINDOW_HEIGHT 80

// Macros for stats windows
#define STATS_WINDOW_HEIGHT 50
#define STATS_WINDOW_WIDTH 40
#define STATS_WINDOW_START_X 80
#define STATS_WINDOW_START_Y 0


Level* curLevel = NULL;
Creature* player = NULL;
Menu* stats = NULL;


int main() {
  player = new Creature('@', TCODColor::red);
  player->setPos(10, 10);
  curLevel = new Level();
  curLevel->generate();
  // Creating our stats menu
  stats = new Menu(STATS_WINDOW_HEIGHT, STATS_WINDOW_WIDTH,
                   STATS_WINDOW_START_X, STATS_WINDOW_START_Y,
                   "Stats Window");
  // Set string in default top position, now 0
  stats->setString("Ur a STINKY doggo!");
  // Now 1
  // Set string in specific index, in this case line 4
  stats->setString("Stinkiest DOGGO around!", 3);
  // This also resets the default position if the index provided
  // is greater than the current default top position

  Creature* thing = new CreatureTest();
  curLevel->addCreature(player);
  curLevel->addCreature(thing);
  thing->setPos(15, 15);
  TCODConsole::initRoot(WINDOW_WIDTH, WINDOW_HEIGHT,"nej_rougelike",false);
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
    stats->drawMenu();
    TCODConsole::flush();
  }
  return 0;
}
