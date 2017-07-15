#include "libtcod.hpp"
#include "Menu.hpp"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

void Menu::drawMenu() {
  TCODConsole::root->setDefaultForeground(TCODColor::red);
  int i = 0;
  for (auto &msg : this->content) {
    TCODConsole::root->print(this->x, this->y + i, msg.c_str());
    i++;
  }
}


std::vector<std::string> Menu::partition(std::string input) {
  int len = std::ceil((float)input.length() / (float)this->width);

  std::vector<std::string> part = std::vector<std::string>();

  for (int i = 0; i < len; i++) {
    if (i == len - 1) {
      // Take section remaining
      part.push_back(input.substr(this->width*i,(this->width + 1)*i ));
    } else {
      // Take last remaining characters
      part.push_back(input.substr(this->width*i,
                                  this->width*i + input.length() % this->width));
    }
  }

  return part;
}

void Menu::setString(std::string message, int index) {

  // If message too long we partition
  // unsigned cast squelches a warning message
  if (message.length() > (unsigned int) this->width) {
    //std::vector<std::string> toAdd = Menu::partition(message);
    if (index != -1) {
      throw std::invalid_argument
        ("Inserting string into specific index failed:\n string too long");
    }
    //for (auto &msg : toAdd) {
    //  this->content.push_back(msg);
    //}
  } else {
    if (index == -1) {
      this->content.push_back(message);
    } else {
      this->content.insert(this->content.begin() + index, message);
    }
  }

  while (this->content.size() > (unsigned int)this->height) {
    this->content.erase(this->content.begin());
  }
}

Menu::Menu() {
}

Menu::Menu(int height, int width, int startx, int starty, std::string name) {
  this->x = startx;
  this->y = starty;
  this->width = width;
  this->height = height;
  this->name = name;

  // Declare content
  this->content = std::vector<std::string>();
}
