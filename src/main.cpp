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
#define STATS_WINDOW_WIDTH 20
#define STATS_WINDOW_START_X 100
#define STATS_WINDOW_START_Y 0

// Macros for message log window
#define LOG_WINDOW_HEIGHT 30
#define LOG_WINDOW_WIDTH 120
#define LOG_WINDOW_START_X 0
#define LOG_WINDOW_START_Y 50


Level* curLevel = NULL;
Creature* player = NULL;
Menu* stats = NULL;
Menu* log = NULL;

int main() {
  player = new Creature('@', TCODColor::red);
  player->setPos(10, 10);
  curLevel = new Level();
  curLevel->generate();
  // Creating our stats menu
  stats = new Menu(STATS_WINDOW_HEIGHT, STATS_WINDOW_WIDTH,
                   STATS_WINDOW_START_X, STATS_WINDOW_START_Y,
                   "Stats Window");
  stats->setString("Hello, this is a test string");
  stats->setString("This string is over 40 characters in length, which means it must be partitioned in order to fit on the screen!!!!!");

  log = new Menu(LOG_WINDOW_HEIGHT, LOG_WINDOW_WIDTH,
		    LOG_WINDOW_START_X, LOG_WINDOW_START_Y,
                   "Log Window");
  // Set string in default top position, now 0
  log->pushMessage("Ur a STINKY doggo!");
  // Now 1
  // Set string in specific index, in this case line 4
  log->pushMessage("Stinkiest DOGGO around!");
  // This also resets the default position if the index provided
  // is greater than the current default top position


  Creature* thing = new CreatureTest();
  curLevel->addCreature(player);
  curLevel->addCreature(thing);
  thing->setPos(15, 15);
  TCODConsole::initRoot(WINDOW_WIDTH, WINDOW_HEIGHT,"nej_roguelike",false);
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
    if(hasActed){
      curLevel->takeTurns();
      //stats->shift(1);
      if (curLevel->canMove(playerx, playery)) {
	player->setPos(playerx, playery);
	std::vector<Item*> itemsAtFeet = curLevel->itemsAt(playerx, playery);
	if(itemsAtFeet.size() > 0){
	  std::string itemString = "";
	  for(auto& it : itemsAtFeet){
	    itemString += it->getName() + " ";
	  }
	  log->pushMessage("At your feet: " + itemString);
	}
      }
    }

    TCODConsole::root->clear();
    curLevel->show();
    stats->drawMenu();
    log->drawMenu();
    TCODConsole::flush();
  }
  return 0;
}
