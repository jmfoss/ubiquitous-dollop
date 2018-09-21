#include "Game.hpp"
#include "Card.hpp"
#include <deque>
#include <algorithm>
#include <random>
#include <iostream>
std::ostream& operator<<(std::ostream& os, const Rank& rank)
{
  switch (rank)
  {
    case 0: return os << "2";
    case 1: return os << "3";
    case 2: return os << "4";
    case 3: return os << "5";
    case 4: return os << "6";
    case 5: return os << "7";
    case 6: return os << "8";
    case 7: return os << "9";
    case 8: return os << "T";
    case 9: return os << "J";
    case 10: return os << "Q";
    case 11: return os << "K";
    case 12: return os << "A";

  }

}

std::ostream& operator<<(std::ostream& os, const Suit& suit)
{
  switch (suit)
  {
    case 0: return os << "S";
    case 1: return os << "C";
    case 2: return os << "D";
    case 3: return os << "H";
  }
}

Game::Game()
{
  std::deque<Card> deck = make_deck();
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(deck.begin(), deck.end(), g);
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

void Game::start()
{
  while (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
  {
    Card one_temp = pop(playerOne);
    Card two_temp = pop(playerTwo);
    std::cout << one_temp.get_rank() << one_temp.get_suit() << " "
              << two_temp.get_rank() << one_temp.get_suit() << std::endl;
    if (one_temp.get_rank() >= two_temp.get_rank())
    {
      playerOne.push_back(one_temp);
      playerOne.push_back(two_temp);
    }
    else if (two_temp.get_rank() > one_temp.get_rank())
    {
      playerTwo.push_back(two_temp);
      playerTwo.push_back(one_temp);
    }
  }
  if (playerOne.begin() != playerOne.end())
  {
    std::cout << "\nPlayer one wins\n";
  }
  else
  {
    std::cout << "\nPlayer two wins\n";
  }
  return;
}

Card Game::pop(std::deque<Card>& playerDeck)
{
  Card temp = playerDeck.front();
  playerDeck.pop_front();
  return temp;
}

void Game::display_hands()
{
  std::cout << "Player one\n";
  int i = 0;
  for (Card card : playerOne)
  {
    ++i;
    std::cout << i << ": " << card.get_rank() << ", " << card.get_suit() << std::endl;
  }
  std::cout << "\nPlayer Two\n";
  i = 0;
  for (Card card : playerTwo)
  {
    ++i;
    std::cout << i << ": " << card.get_rank() << ", " << card.get_suit() << std::endl;
  }
  return;
}
