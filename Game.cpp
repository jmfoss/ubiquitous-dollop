#include "Game.hpp"
#include "Card.hpp"
#include <deque>
#include <utility>
#include <algorithm>
#include <random>
#include <iostream>

using Spoil = std::pair<Card, Card>;

Game::Game()
{
  deck = make_deck();
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
    std::cout << "\nfight: ";
    Card one_temp = pop(playerOne);
    Card two_temp = pop(playerTwo);
    std::cout << one_temp << " " << two_temp;
    if (one_temp.get_rank() > two_temp.get_rank())
    {
      std::cout << "\nWin1: " << one_temp;
      playerOne.push_back(one_temp);
      playerOne.push_back(two_temp);
    }
    else if (two_temp.get_rank() > one_temp.get_rank())
    {
      std::cout << "\nWin2: " << two_temp;
      playerTwo.push_back(two_temp);
      playerTwo.push_back(one_temp);
    }
    else
    {
      std::cout << "\nWar: ";
      Spoil spoil = war(one_temp, two_temp);
      if (spoil.first.get_rank > spoil.second.get_rank)
      {
        std::cout << "\nadd1: " << one_temp;
        playerOne.push_back(one_temp);
        playerOne.push_back(two_temp);
      }
      else
      {
        std::cout << "\nadd2: " << two_temp;
        playerTwo.push_back(two_temp);
        playerTwo.push_back(one_temp);
      }
    }
  }
  if (playerTwo.begin() != playerTwo.end())
  {
    std::cout << "\nPlayer two wins\n";
  }
  else
  {
    std::cout << "\nPlayer one wins\n";
  }
  return;
}

Card Game::pop(std::deque<Card>& playerDeck)
{
  Card temp = playerDeck.front();
  playerDeck.pop_front();
  return temp;
}

Spoil war()
{
  Card one_temp = pop(playerOne);
  Card two_temp = pop(playerTwo);
  if (one_temp.get_rank() > two_temp.get_rank())
  {
    std::cout << "\nWin1: " << one_temp << " " << two_temp;
    playerOne.push_back(one_temp);
    playerOne.push_back(two_temp);
    return Spoil (one_temp, two_temp);
  }
  else if (two_temp.get_rank() > one_temp.get_rank())
  {
    std::cout << "\nWin2: " << two_temp << " " << one_temp;
    playerTwo.push_back(two_temp);
    playerTwo.push_back(one_temp);
    return Spoil (one_temp, two_temp);
  }
  else
  {
    Spoil spoil = war(one_temp, two_temp);
    if (spoil.first.get_rank > spoil.second.get_rank)
    {
      std::cout << "\nadd1: " << one_temp << " " << two_temp;
      playerOne.push_back(one_temp);
      playerOne.push_back(two_temp);
      return spoil
    }
    else
    {
      std::cout << "\nadd2: " << two_temp << " " << one_temp;
      playerTwo.push_back(two_temp);
      playerTwo.push_back(one_temp);
      return spoil
    }
  }
}
