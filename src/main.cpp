#include "libtcod.hpp"
#include "Stairs.hpp"
#include "Creature.hpp"
#include "Level.hpp"
#include "Item.hpp"
#include "Menu.hpp"
#include "TargetingSystem.hpp"
#include "CreatureDatabase.hpp"

#define WINDOW_WIDTH 120
#define WINDOW_HEIGHT 80

// Macros for stats windows
#define STATS_WINDOW_HEIGHT 80
#define STATS_WINDOW_WIDTH 30
#define STATS_WINDOW_START_X 90
#define STATS_WINDOW_START_Y 0

// Macros for message log window
#define LOG_WINDOW_HEIGHT 30
#define LOG_WINDOW_WIDTH 90
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
  targetingSystem = new TargetingSystem();

  Creature* thing = new CreatureTest();
  curLevel->addCreature(player);
  curLevel->addCreature(thing);
  thing->setPos(15, 15);
  TCODConsole::initRoot(WINDOW_WIDTH, WINDOW_HEIGHT,"nej_roguelike",false);
  while ( !TCODConsole::isWindowClosed() ) {
    bool hasActed = false;
    int playerx, playery;
    player->getPos(&playerx, &playery);
    if(targetingSystem->getIsTargeting()){
      targetingSystem->stillTargeting();
    }
    else {
      TCOD_key_t key;
      TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
      
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
	else if(key.c == 'l'){
	  //Look
	  targetingSystem->startTargeting();
	}
	else if(key.c == '>'){
	  //Enter
	  curLevel->enterAt(playerx, playery);
	  hasActed = true;
	}
	break;
      default:break;
      }
    }
    
    if(hasActed){
      // Check if the player has actually moved
      int cx, cy;
      player->getPos(&cx, &cy);
      // If player has not actually moved, just acted
      if ((cx == playerx && cy == playery)) {
        // Otherwise, standard behaviour
        // Might want to pick viewing items?
        std::vector<Item*> itemsAtFeet = curLevel->itemsAt(playerx, playery);
        if(itemsAtFeet.size() > 0){
          std::string itemString = "";
          for(auto& it : itemsAtFeet){
            itemString += it->getName() + " ";
          }
          msgLog->pushMessage("At your feet: " + itemString);
        }
      } else if (curLevel->canMove(playerx, playery)) {
        // Otherwise, if the player is actually moving
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
	curLevel->computeFov();
      }

      // Other creatures take their turns after the players
      // has been fully processed
      std::vector<std::string> otherTurnResults = curLevel->takeTurns();

      for (auto &msg : otherTurnResults ){
        if (msg == "") continue;
        msgLog->pushMessage(msg);
      }
    }

    TCODConsole::root->clear();
    curLevel->show();
    if(targetingSystem->getIsTargeting()){
      int cx, cy;
      targetingSystem->getCursorPos(&cx, &cy);
      TCODConsole::root->setChar(cx, cy, 'X');
      TCODConsole::root->setCharBackground(cx, cy, TCODColor::orange);
      TCODConsole::root->setCharForeground(cx, cy, TCODColor::red);
    }
    stats->drawMenu();
    msgLog->drawMenu();
    TCODConsole::flush();
  }
  return 0;
}
