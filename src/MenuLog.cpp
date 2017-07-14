#include "MenuLog.hpp"

void MenuLog::drawMenu(){
  int i = 0;
  for(auto& message : this->messages){
    this->content[i] = message;
    i++;
  }
  Menu::drawMenu();
}

void MenuLog::pushMessage(std::string str){
  this->messages.push_back(str);
}

void MenuLog::popMessage(){
  return this->messages.pop_back();
}

MenuLog::MenuLog(int height, int width, int startx, int starty, std::string name) : Menu(height, width, startx, starty, name) {
}
