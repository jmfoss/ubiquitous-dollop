#include "Game.hpp"
#include <iostream>

int main()
{
  Game war;
  const int NUM_GAMES = 10000;
  int total_turns = 0, min_turns = 0, max_turns = 0;
  for (int i = 0, turns = 0; i < NUM_GAMES; ++i)
  {
    turns = war.start();
    if (turns > max_turns)
    {
      max_turns = turns;
    }
    else if (turns < min_turns || min_turns == 0)
    {
      min_turns = turns;
    }
    total_turns += turns;
    std::cout << "Number of turns for game: " << turns << std::endl;
    war.shuffle();
    war.split();
  }
  std::cout << "Shortest game by turns: " << min_turns << std::endl;
  std::cout << "Longest game by turns: " << max_turns << std::endl;
  std::cout << "Averge amount of turns per game: "
            << total_turns / NUM_GAMES << std::endl;

  return 0;
}
