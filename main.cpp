#include "Game.hpp"
#include <iostream>

int main()
{
  Game war;
  int total_turns = 0;
  for (int i = 0; i < 10; ++i)
  {
    total_turns += war.start();
    war.shuffle();
    war.split();
  }
  std::cout << std::endl << "Averge amount of turns per game: "
            << total_turns / 10;

  return 0;
}
