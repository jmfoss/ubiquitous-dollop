#include "Game.hpp"
#include "Card.hpp"
#include <deque>
#include <utility>
#include <algorithm>
#include <random>
#include <iostream>


//creates the deck, shuffles it and splits the deck into
//two hands, one for each player
Game::Game()
{
  deck = make_deck();
  shuffle();
  split();
}

//splits deck into two hands
//every other goes to each hand
void Game::split()
{
  while (deck.begin() != deck.end())
  {
    playerOne.push_front(deck.front());
    deck.pop_front();
    playerTwo.push_front(deck.front());
    deck.pop_front();
  }
}

//shuffles deck
void Game::shuffle()
{
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(deck.begin(), deck.end(), g);
}

//creates a deck of 52 cards
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

//runs one game of war
int Game::start()
{
  int turns = 0;
  //loops while each deck is not empty
  while (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
  {
    //keeps track of turns
    ++turns;
    //takes off first card from the hand and returns the card
    oneSpoils.push_back(pop(playerOne));
    twoSpoils.push_back(pop(playerTwo));
    //checks which card is greater and places
    //the card into the winning hand
    if (oneSpoils.back.get_rank() > twoSpoils.back.get_rank())
    {
      playerOne.push_back(pop(oneSpoils));
      playerOne.push_back(pop(twoSpoils));
    }
    else if (twoSpoils.back.get_rank() > oneSpoils.back.get_rank())
    {
      playerTwo.push_back(pop(twoSpoils));
      playerTwo.push_back(pop(oneSpoils));
    }
    //if the cards are equal, it goes into war
    else
    {
      //Check if either hand is empty before entering war
      if (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
      {
        //calls the war function
        war();
        //using winning and losing spoil to determine where
        //to place burnt cards
        if (oneSpoils.back.get_rank() > twoSpoils.back.get_rank())
        {
          while (oneSpoils.begin() != oneSpoils.end())
          {
            playerOne.push_back(pop(oneSpoils));
            playerOne.push_back(pop(twoSpoils));
          }
        }
        else if (twoSpoils.back.get_rank() > oneSpoils.back.get_rank())
        {
          while (twoSpoils.begin() != twoSpoils.end())
          {
            playerTwo.push_back(pop(twoSpoils));
            playerTwo.push_back(pop(oneSpoils));
          }
        }
        else
        {
          if (playerOne.begin() != playerOne.end())
          {
            while (oneSpoils.begin() != oneSpoils.end())
            {
              playerOne.push_back(pop(oneSpoils));
              playerOne.push_back(pop(twoSpoils));
            }
          }
          else
          {
            while (twoSpoils.begin() != twoSpoils.end())
            {
              playerTwo.push_back(pop(twoSpoils));
              playerTwo.push_back(pop(oneSpoils));
            }
          }
        }
      }
      else
      {
        if (oneSpoils.back.get_rank() > twoSpoils.back.get_rank())
        {
          while (oneSpoils.begin() != oneSpoils.end())
          {
            playerOne.push_back(pop(oneSpoils));
            playerOne.push_back(pop(twoSpoils));
          }
        }
        else if (two_burn.get_rank() > one_burn.get_rank())
        {
          while (twoSpoils.begin() != twoSpoils.end())
          {
            playerTwo.push_back(pop(twoSpoils));
            playerTwo.push_back(pop(oneSpoils));
          }
        }
        else
        {
          if (playerOne.begin() != playerOne.end())
          {
            while (oneSpoils.begin() != oneSpoils.end())
            {
              playerOne.push_back(pop(oneSpoils));
              playerOne.push_back(pop(twoSpoils));
            }
          }
          else
          {
            while (twoSpoils.begin() != twoSpoils.end())
            {
              playerTwo.push_back(pop(twoSpoils));
              playerTwo.push_back(pop(oneSpoils));
            }
          }
        }
      }
    }
  }

  //checks which hand is not empty to determine who won.
  if (playerTwo.begin() != playerTwo.end())
  {
    std::cout << "Player two won!\n";
    playerTwo.swap(deck);
  }
  else
  {
    std::cout << "Player one won!\n";
    playerOne.swap(deck);
  }
  //returns number of turns
  return turns;
}

//takes off top card and returns it
//passed a deque of type Card
Card Game::pop(std::deque<Card>& playerDeck)
{
  Card temp = playerDeck.front();
  playerDeck.pop_front();
  return temp;
}

//conducts war scenario
//uses recursion if card continue to equal each other
void Game::war()
{
  //burn
  oneSpoils.push_back(pop(playerOne));
  twoSpoils.push_back(pop(playerTwo));
  //compares the two cards
  if (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
  {
    oneSpoils.push_back(pop(playerOne));
    twoSpoils.push_back(pop(playerTwo));
    if (oneSpoils.back.get_rank() == twoSpoils.back.get_rank())
    {
      if (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
      {
        war();
      }
    }
  }
  return;
}
