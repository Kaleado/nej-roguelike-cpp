#include "libtcod.hpp"
#include "Menu.hpp"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

Menu* stats = NULL;
Menu* msgLog = NULL;

void Menu::drawMenu() {
  TCODConsole::root->setDefaultBackground(this->backgroundColor);
  TCODConsole::root->setDefaultForeground(this->textColor);
  int i = 0;
  for (auto &msg : this->content) {
    int j = 0;
    for (auto &ch : msg) {
      TCODConsole::root->putCharEx(this->x + j, this->y + i, ch,
                                   this->textColor,this->backgroundColor);
      j++;
    }

    // Finish off the pane color for the row
    while (this->width - j > 0) {
      TCODConsole::root->putCharEx(this->x + j, this->y + i, ' ',
                                   this->textColor,this->backgroundColor);
      j++;
    }
    i++;
  }

  // Finish off the color for the rest of the pane
  while (this->height - i >= 0) {
    for (int j = 0; j < this->width; j++) {
      TCODConsole::root->putCharEx(this->x + j, this->y + i, ' ',
                                   this->textColor,this->backgroundColor);
    }
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
    std::vector<std::string> toAdd = Menu::partition(message);
    if (index != -1) {
      throw std::invalid_argument
        ("Inserting string into specific index failed:\n string too long");
    }
    for (auto &msg : toAdd) {
      this->content.push_back(msg);
    }
  } else {
    if (index == -1) {
      this->content.push_back(message);
    } else {
      this->content.insert(this->content.begin() + index, message);
    }
  }

  while (this->content.size() > (unsigned int)this->height) {
    // Remove messages until the amount of messages we have fits in the window
    this->content.erase(this->content.begin());
  }
}

void Menu::pushMessage(std::string str){
  this->content.push_back(str);
  // Remove the bottom message if we have too many messages in our vector
  if (this->content.size() > (unsigned int) this->height)
    this->content.erase(this->content.begin());
}

void Menu::popMessage(){
  return this->content.pop_back();
}


Menu::Menu() {
}

Menu::Menu(int height, int width, int startx, int starty, std::string name,
           TCODColor text, TCODColor bg) {
  // Dimensions
  this->x = startx;
  this->y = starty;
  this->width = width;
  this->height = height;
  this->name = name;

  //Color
  this->textColor = text;
  this->backgroundColor = bg;

  // Declare content
  this->content = std::vector<std::string>();
}
