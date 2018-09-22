#include "Game.hpp"
#include <iostream>

int main()
{
  Game war;
  int total_turns = 0;
  for (int i = 0; i < 1000; ++i)
  {
    total_turns += war.start();
    war.shuffle();
  }
  std::cout << std::endl << "Averge amount of turns per game: "
            << total_turns / 1000;

  return 0;
}
