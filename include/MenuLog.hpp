#ifndef MENU_LOG_HPP
#define MENU_LOG_HPP

#include "Menu.hpp"
#include "libtcod.hpp"
#include <string>
#include <vector>

class MenuLog : public Menu {
private:
  std::vector<std::string> messages;
public:
  void drawMenu();
  void pushMessage(std::string str);
  void popMessage();
  MenuLog(int height, int width, int startx, int starty, std::string name);
};

#endif
