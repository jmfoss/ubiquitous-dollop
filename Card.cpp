#include "Card.hpp"
#include <iostream>

Card::Card(Rank r, Suit s) : m_rank(r), m_suit(s)
{

}

std::ostream& operator<<(std::ostream& os, Card card)
{
  switch (card.m_rank)
  {
    case 0:
      os << "2";
      break;
    case 1:
      os << "3";
      break;
    case 2:
      os << "4";
      break;
    case 3:
      os << "5";
      break;
    case 4:
      os << "6";
      break;
    case 5:
      os << "7";
      break;
    case 6:
      os << "8";
      break;
    case 7:
      os << "9";
      break;
    case 8:
      os << "T";
      break;
    case 9:
      os << "J";
      break;
    case 10:
      os << "Q";
      break;
    case 11:
      os << "K";
      break;
    case 12:
      os << "A";
      break;
  }
  switch (card.m_suit)
  {
    case 0:
      os << "S";
      break;
    case 1:
      os << "C";
      break;
    case 2:
      os << "D";
      break;
    case 3:
      os << "H";
      break;
  }
  return os;

}

std::ostream& operator<<(std::ostream& os, Suit& suit)
{

}
