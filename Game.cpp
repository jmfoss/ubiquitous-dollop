#include "Game.hpp"
#include "Card.hpp"
#include <deque>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <cstdlib>

Game::Game()
{
  std::deque<Card> deck = make_deck();
  std::srand(std::time(0));
  std::shuffle(deck.begin(), deck.end(), std::rand());
  while (deck.begin() != deck.end())
  {
    playerOne.push_front(deck.front());
    deck.pop_front();
    playerTwo.push_front(deck.front());
    deck.pop_front();
  }
}

std::deque<Card> Game::make_deck()
{
  return std::deque<Card> { {Ace, Spades},
                            {Two, Spades},
                            {Three, Spades},
                            {Four, Spades},
                            {Five, Spades},
                            {Six, Spades},
                            {Seven, Spades},
                            {Eight, Spades},
                            {Nine, Spades},
                            {Ten, Spades},
                            {Jack, Spades},
                            {Queen, Spades},
                            {King, Spades},
                            {Ace, Clubs},
                            {Two, Clubs},
                            {Three, Clubs},
                            {Four, Clubs},
                            {Five, Clubs},
                            {Six, Clubs},
                            {Seven, Clubs},
                            {Eight, Clubs},
                            {Nine, Clubs},
                            {Ten, Clubs},
                            {Jack, Clubs},
                            {Queen, Clubs},
                            {King, Clubs},
                            {Ace, Diamonds},
                            {Two, Diamonds},
                            {Three, Diamonds},
                            {Four, Diamonds},
                            {Five, Diamonds},
                            {Six, Diamonds},
                            {Seven, Diamonds},
                            {Eight, Diamonds},
                            {Nine, Diamonds},
                            {Ten, Diamonds},
                            {Jack, Diamonds},
                            {Queen, Diamonds},
                            {King, Diamonds},
                            {Ace, Hearts},
                            {Two, Hearts},
                            {Three, Hearts},
                            {Four, Hearts},
                            {Five, Hearts},
                            {Six, Hearts},
                            {Seven, Hearts},
                            {Eight, Hearts},
                            {Nine, Hearts},
                            {Ten, Hearts},
                            {Jack, Hearts},
                            {Queen, Hearts},
                            {King, Hearts} };
}

void Game::display_hands()
{
  std::cout << "Player one\n";
  int i = 0;
  for (Card card : playerOne)
  {
    ++i;
    std::cout << i << ": " << card.get_rank() << ", " << card.get_rank() << std::endl;
  }
  std::cout << "\nPlayer Two\n";
  i = 0;
  for (Card card : playerTwo)
  {
    ++i;
    std::cout << i << ": " << card.get_rank() << ", " << card.get_rank() << std::endl;
  }
  return;
}
