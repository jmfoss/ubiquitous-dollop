#include "card.hpp"

#include <iostream>


std::ostream&
operator<<(std::ostream& os, Rank r)
{
  switch (r) {
  case Ace: return os << "A";
  case Two: return os << "2";
  case Three: return os << "3";
  case Four: return os << "4";
  case Five: return os << "5";
  case Six: return os << "6";
  case Seven: return os << "7";
  case Eight: return os << "8";
  case Nine: return os << "9";
  case Ten: return os << "T";
  case Jack: return os << "J";
  case Queen: return os << "Q";
  case King: return os << "K";
  }
}

std::ostream&
operator<<(std::ostream& os, Suit s)
{
  switch (s)
  {
  case Spades: return os << "\u2660";
  case Clubs: return os << "\u2663";
  case Diamonds: return os << "\u2662";
  case Hearts: return os << "\u2661";
  }
}

std::ostream&
operator<<(std::ostream& os, Color c)
{
  if (c == Black)
    return os << "B";
  else
    return os << "R";
}


std::ostream&
operator<<(std::ostream& os, Card c)
{
  return os << c.rank << c.suit;
}

std::ostream&
operator<<(std::ostream& os, Joker j)
{
  return os << j.color;
}
