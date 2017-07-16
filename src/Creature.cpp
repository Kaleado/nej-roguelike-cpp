#include "libtcod.hpp"
#include "Creature.hpp"
#include "Level.hpp"
#include "Item.hpp"
#include <random>
#include <ctime>
#include <string>

Creature* player = NULL;

void Creature::setPos(int nx, int ny){
  this->x = nx;
  this->y = ny;
}

std::string Creature::move(int nx, int ny, Level* lvl) {
  Creature * enemy = lvl->creaturesAt(nx,ny);
  if (enemy != NULL) {
    return this->attack(nx,ny,enemy);
  } else {
    this->setPos(nx,ny);
    return "";
  }
}

void Creature::getPos(int* rx, int* ry){
    *rx = this->x;
    *ry = this->y;
}

void Creature::pickup(Level* lev) {
  std::vector<Item*> items = lev->itemsAt(this->x, this->y);

  // Iterate through items, add to inventory and remove from map
  for (auto &it : items) {
    this->inventory.push_back(it);
    lev->removeItem(it);
  }
}

void Creature::showAt(int sx, int sy){
  TCODConsole::root->setChar(sx, sy, character);
  TCODConsole::root->setCharForeground(sx, sy, colour);
}

void Creature::show(){
  showAt(x, y);
}

std::string Creature::takeTurn(Level* lev){
  return "";
}

std::string Creature::getName() {
  return this->name;
}

bool Creature::isDead() {
  return (this->hp <= 0) ? true : false;
}

/* Called on the condition that an enemy Creature exists in the square
 * that this Creature is moving to.
 * Probability distribution guide for damage found here:
 * http://www.redblobgames.com/articles/probability/damage-rolls.html
 */
std::string Creature::attack(int x, int y, Creature* enemy) {

  // Random numbers, to give damage some meaningful distribution
  // Some random number based on curr time
  std::srand(std::time(0));

  unsigned int dmg = 0;

  // We roll three times, and drop the minimum value to get a higher-biased
  // distribution. Damage ranges between 1 and strength.

  unsigned int r1 = (rand() % (this->strength)) + 1;
  unsigned int r2 = (rand() % (this->strength)) + 1;
  unsigned int r3 = (rand() % (this->strength)) + 1;

  dmg = r1 + r2 +r3;

  // drop the minimum of the 3 rolls for a biased shift
  unsigned int min = std::min(std::min(r1, r2), std::min(r2,r3));
  dmg = dmg - min;

  // Critical hits - damage is doubled 2% of the time
  if (((int) rand() % 100) < 2)
    dmg = dmg*2;

  enemy->hpDelta(dmg);

  std::string status = enemy->name + " took " + std::to_string(dmg)
    + " damage from "
    + this->name + "!";

  return status;
}

void Creature::hpDelta(int dmg) {
  this->hp += dmg;
}

Creature::Creature(){
}

Creature::Creature(int character, TCODColor colour, std::string name,
                   int str, int dex,
                   int con , int intel, int wis, int cha,
                   int maxHP){
  this->colour = colour;
  this->character = character;
  this->name = name;

  //stats
  this->strength = str;
  this->dexterity = dex;
  this->constitution = con;
  this->intelligence = intel;
  this->wisdom = wis;
  this->charisma = cha;
  this->maxHp = maxHP;
  this->hp = maxHP;
}
