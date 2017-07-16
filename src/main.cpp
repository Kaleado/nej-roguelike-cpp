#include "libtcod.hpp"
#include "Stairs.hpp"
#include "Creature.hpp"
#include "Level.hpp"
#include "Item.hpp"
#include "Menu.hpp"
#include "CreatureDatabase.hpp"

#define WINDOW_WIDTH 120
#define WINDOW_HEIGHT 80

// Macros for stats windows
#define STATS_WINDOW_HEIGHT 80
#define STATS_WINDOW_WIDTH 20
#define STATS_WINDOW_START_X 100
#define STATS_WINDOW_START_Y 0

// Macros for message log window
#define LOG_WINDOW_HEIGHT 30
#define LOG_WINDOW_WIDTH 100
#define LOG_WINDOW_START_X 0
#define LOG_WINDOW_START_Y 50

int main() {
  srand(time(NULL));
  player = new Creature('@', TCODColor::red, "Player");
  player->setPos(10, 10);
  Level* otherLevel = new Level();
  otherLevel->generate();
  curLevel = new Level();
  curLevel->generate();
  curLevel->setTileType(12, 12, new TileTypeStairs('>', TCODColor::red, true, TCODColor::black, otherLevel, 10, 10));
  // Creating our stats menu
  stats = new Menu(STATS_WINDOW_HEIGHT, STATS_WINDOW_WIDTH,
                   STATS_WINDOW_START_X, STATS_WINDOW_START_Y,
                   "Stats Window");
  stats->setString("This string is over 40 characters in length, which means it must be partitioned in order to fit on the screen!!!!!");

  msgLog = new Menu(LOG_WINDOW_HEIGHT, LOG_WINDOW_WIDTH,
		    LOG_WINDOW_START_X, LOG_WINDOW_START_Y,
                 "Log Window", TCODColor::black, TCODColor::white);
  // Set string in default top position, now 0
  msgLog->pushMessage("Ur a STINKY doggo!");
  // Now 1
  // Set string in specific index, in this case line 4
  msgLog->pushMessage("Stinkiest DOGGO around!");
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
      else if(key.c == '>'){
        //Enter
        curLevel->enterAt(playerx, playery);
        hasActed = true;
      }
      break;
    default:break;
    }

    if(hasActed){
      if (curLevel->canMove(playerx, playery)) {
        std::string status = player->move(playerx, playery, curLevel);
        if (status != "") {
          // If an event happened during movement
          msgLog->pushMessage(status);
        } else {
          // Otherwise, standard behaviour
          std::vector<Item*> itemsAtFeet = curLevel->itemsAt(playerx, playery);
          if(itemsAtFeet.size() > 0){
            std::string itemString = "";
            for(auto& it : itemsAtFeet){
              itemString += it->getName() + " ";
            }
	    msgLog->pushMessage("At your feet: " + itemString);
          }
        }
      }
      // Other creatures take their turns after the players
      // has been fully processed
      curLevel->takeTurns();
    }

    TCODConsole::root->clear();
    curLevel->show();
    stats->drawMenu();
    msgLog->drawMenu();
    TCODConsole::flush();
  }
  return 0;
}
