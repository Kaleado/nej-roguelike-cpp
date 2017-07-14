#include "libtcod.hpp"
#include "Menu.hpp"
#include <string>

void Menu::drawMenu() {
  TCODConsole::root->setDefaultForeground(TCODColor::red);
  for (int i = 0; i < this->height; i++) {
    TCODConsole::root->print(this->x, this->y + i, this->content[i].c_str());
  }
}

void Menu::shift(int amount) {
  for (int i =0 ; i < this->height; i++){
    if (amount + i < this->height) {
      // If in bounds, copy the string and erase string copied from
      this->content[i] = this->content[amount + i];
      this->content[amount + i ] = "";
    } else {
      // If out of bounds, just copy empty string
      this->content[i] = "";
    }
  }
}

void Menu::setString(std::string message, int index) {
  // If index provided and index in range
  if (index >= 0 && index < this->height) {
    this->content[index] = message;
    if (index > top) top = index + 1;
  // If index not provided and content not full
  } else if (this->top < this->height) {
    this->content[top] = message;
    this->top++;
  }
}

Menu::Menu(int height, int width, int startx, int starty, std::string name) {
  this->x = startx;
  this->y = starty;
  this->width = width;
  this->height = height;
  this->name = name;

  this->content = new std::string[height];
  this->top = 0;
}
