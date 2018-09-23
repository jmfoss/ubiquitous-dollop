#include "Game.hpp"
#include "Card.hpp"
#include <deque>
#include <utility>
#include <algorithm>
#include <random>
#include <iostream>

using Spoil = std::pair<Card, Card>;

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
    Card one_temp = pop(playerOne);
    Card two_temp = pop(playerTwo);
    //checks which card is greater and places
    //the card into the winning hand
    if (one_temp.get_rank() > two_temp.get_rank())
    {
      playerOne.push_back(one_temp);
      playerOne.push_back(two_temp);
    }
    else if (two_temp.get_rank() > one_temp.get_rank())
    {
      playerTwo.push_back(two_temp);
      playerTwo.push_back(one_temp);
    }
    //if the cards are equal, it goes into war
    else
    {
      std::cout << "war\n";
      //Check if either hand is empty before entering war
      if (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
      {
        //burnt cards
        Card one_burn = pop(playerOne);
        Card two_burn = pop(playerTwo);
        if (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
        {
          //calls the war function and returns the
          //final winning and losing card
          Spoil spoil = war();
          //using winning and losing spoil to determine where
          //to place burnt cards
          if (spoil.first.get_rank() > spoil.second.get_rank())
          {
            playerOne.push_back(one_burn);
            playerOne.push_back(two_burn);
            playerOne.push_back(one_temp);
            playerOne.push_back(two_temp);
          }
          else if (spoil.second.get_rank() > spoil.first.get_rank())
          {
            playerTwo.push_back(two_burn);
            playerTwo.push_back(one_burn);
            playerTwo.push_back(two_temp);
            playerTwo.push_back(one_temp);
          }
          else
          {
            if (playerOne.begin() != playerOne.end())
            {
              playerOne.push_back(one_burn);
              playerOne.push_back(two_burn);
              playerOne.push_back(one_temp);
              playerOne.push_back(two_temp);
            }
            else
            {
              playerTwo.push_back(two_burn);
              playerTwo.push_back(one_burn);
              playerTwo.push_back(two_temp);
              playerTwo.push_back(one_temp);
            }
          }
        }
        else
        {
          if (one_burn.get_rank() > two_burn.get_rank())
          {
            playerOne.push_back(one_burn);
            playerOne.push_back(two_burn);
            playerOne.push_back(one_temp);
            playerOne.push_back(two_temp);
          }
          else if (two_burn.get_rank() > one_burn.get_rank())
          {
            playerTwo.push_back(two_burn);
            playerTwo.push_back(one_burn);
            playerTwo.push_back(two_temp);
            playerTwo.push_back(one_temp);
          }
          else
          {
            if (playerOne.begin() != playerOne.end())
            {
              playerOne.push_back(one_burn);
              playerOne.push_back(two_burn);
              playerOne.push_back(one_temp);
              playerOne.push_back(two_temp);
            }
            else
            {
              playerTwo.push_back(two_burn);
              playerTwo.push_back(one_burn);
              playerTwo.push_back(two_temp);
              playerTwo.push_back(one_temp);
            }
          }
        }
      }
      else
      {
        if (playerOne.begin() != playerOne.end())
        {
          playerOne.push_back(one_temp);
          playerOne.push_back(two_temp);
        }
        else
        {
          playerTwo.push_back(two_temp);
          playerTwo.push_back(one_temp);
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
  int cards = 0;
  for (Card a : deck)
  {
    ++cards;
  }
  std::cout << "card count: " << cards << std::endl;
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
Spoil Game::war()
{
  //pops of first card
  Card one_temp = pop(playerOne);
  Card two_temp = pop(playerTwo);
  //compares the two cards
  if (one_temp.get_rank() > two_temp.get_rank())
  {
    //places spoils in winning hand
    playerOne.push_back(one_temp);
    playerOne.push_back(two_temp);
    //calls spoil, passed the winning and losing cards
    //returning them as a pair
    return Spoil (one_temp, two_temp);
  }
  else if (two_temp.get_rank() > one_temp.get_rank())
  {
    playerTwo.push_back(two_temp);
    playerTwo.push_back(one_temp);
    return Spoil (one_temp, two_temp);
  }
  else // if the cards are equal
  {
    std::cout << "war\n";
    //Check if either hand is empty before entering war
    if (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
    {
      Card one_burn = pop(playerOne);
      Card two_burn = pop(playerTwo);
      //Check if either hand is empty after burn and if so compares burns
      if (playerOne.begin() != playerOne.end() && playerTwo.begin() != playerTwo.end())
      {
        //calls the war function and returns the
        //final winning and losing card
        Spoil spoil = war();
        //using winning and losing spoil to determine where
        //to place burnt cards
        if (spoil.first.get_rank() > spoil.second.get_rank())
        {
          playerOne.push_back(one_burn);
          playerOne.push_back(two_burn);
          playerOne.push_back(one_temp);
          playerOne.push_back(two_temp);
          return spoil;
        }
        else if (spoil.second.get_rank() > spoil.first.get_rank())
        {
          playerTwo.push_back(two_burn);
          playerTwo.push_back(one_burn);
          playerTwo.push_back(two_temp);
          playerTwo.push_back(one_temp);
          return spoil;
        }
        else
        {
          if (playerOne.begin() != playerOne.end())
          {
            playerOne.push_back(one_burn);
            playerOne.push_back(two_burn);
            playerOne.push_back(one_temp);
            playerOne.push_back(two_temp);
          }
          else
          {
            playerTwo.push_back(two_burn);
            playerTwo.push_back(one_burn);
            playerTwo.push_back(two_temp);
            playerTwo.push_back(one_temp);
          }
          return spoil;
        }
      }
      else
      {
        if (one_burn.get_rank() > two_burn.get_rank())
        {
          playerOne.push_back(one_burn);
          playerOne.push_back(two_burn);
          playerOne.push_back(one_temp);
          playerOne.push_back(two_temp);
          return Spoil (one_burn, two_burn);
        }
        else if (two_burn.get_rank() > one_burn.get_rank())
        {
          playerTwo.push_back(two_burn);
          playerTwo.push_back(one_burn);
          playerTwo.push_back(two_temp);
          playerTwo.push_back(one_temp);
          return Spoil (one_burn, two_burn);
        }
        else
        {
          if (playerOne.begin() != playerOne.end())
          {
            playerOne.push_back(one_burn);
            playerOne.push_back(two_burn);
            playerOne.push_back(one_temp);
            playerOne.push_back(two_temp);
          }
          else
          {
            playerTwo.push_back(two_burn);
            playerTwo.push_back(one_burn);
            playerTwo.push_back(two_temp);
            playerTwo.push_back(one_temp);
          }
          return Spoil (one_burn, two_burn);
        }
      }
    }
    else
    {
      if (playerOne.begin() != playerOne.end())
      {
        playerOne.push_back(one_temp);
        playerOne.push_back(two_temp);
      }
      else
      {
        playerTwo.push_back(two_temp);
        playerTwo.push_back(one_temp);
      }
      //returns equal cards if player runs out of cards
      return Spoil (one_temp, two_temp);
    }
  }
}
