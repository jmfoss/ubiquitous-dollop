#ifndef GAME_HPP
#define GAME_HPP

#include "Card.hpp"
#include <deque>

class Game
{
private:
  std::deque<Card> playerOne;
  std::deque<Card> playerTwo;
  std::deque<Card> make_deck();
  Card pop(std::deque<Card>& playerDeck);
public:
  Game();
  void start();
  void display_hands();
};


#endif
