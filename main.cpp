#include "Game.hpp"
#include <iostream>

int main()
{
  Game war;
  int num = 100;
  int total_turns = 0;
  for (int i = 0, turns = 0; i < num; ++i)
  {
    turns = war.start();
    total_turns += turns;
    std::cout << "Number of turns for game: " << turns << std::endl;
    war.shuffle();
    war.split();
  }
  std::cout << std::endl << "Averge amount of turns per game: "
            << total_turns / num;

  return 0;
}
