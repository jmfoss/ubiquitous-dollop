#ifndef GAME_HPP
#define GAME_HPP

#include "Card.hpp"
#include <deque>
#include <utility>
#include <iostream>

class Game
{
private:
  std::deque<Card> deck;
  std::deque<Card> playerOne;
  std::deque<Card> oneSpoils;
  std::deque<Card> playerTwo;
  std::deque<Card> twoSpoils;
  std::deque<Card> spoils;
  std::deque<Card> make_deck();
  bool compare();
  void war();
  void add(bool player);
  Card pop(std::deque<Card>& playerDeck);

public:
  Game();
  int start();
  void shuffle();
  void split();
};


#endif
