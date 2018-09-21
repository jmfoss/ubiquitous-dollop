#include "Game.hpp"
#include <iostream>

int main()
{
  Game war;
  war.display_hands();
  std::cout << std::endl << "start game" << std::endl;
  war.start();
  return 0;
}
