#ifndef GAME_HPP
#define GAME_HPP

#include "Card.hpp"
#include <deque>
#include <iostream>

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
  friend std::ostream& operator<<(std::ostream& os, Rank rank);
  friend std::ostream& operator<<(std::ostream& os, Suit suit);
};


#endif
