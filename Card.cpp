#include "Card.hpp"
#include <iostream>

Card::Card(Rank r, Suit s) : m_rank(r), m_suit(s)
{

}
/*
std::ostream& operator<<(std::ostream& os, Rank rank)
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

std::ostream& operator<<(std::ostream& os, Suit suit)
{
  switch (suit)
  {
    case 0:  os << "S";
      return os;
    case 1:  os << "C";
      return os;
    case 2: os << "D";
      return os;
    case 3: os << "H";
      return os;
  }
}
  */
