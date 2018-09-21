#include "Card.hpp"
#include <iostream>

Card::Card(Rank r, Suit s) : m_rank(r), m_suit(s)
{

}

std::ostream& operator<<(std::ostream& os, Rank rank)
{
  switch (rank)
  {
    case 0: return '2';
    case 1: return '3';
    case 2: return '4';
    case 3: return '5';
    case 4: return '6';
    case 5: return '7';
    case 6: return '8';
    case 7: return '9';
    case 8: return 'T';
    case 9: return 'J';
    case 10: return 'Q';
    case 11: return 'K';
    case 12: return 'A';

  }

}

std::ostream& operator<<(std::ostream& os, Suit suit)
{
  switch (suit)
  {
    case 0: return 'S';
    case 1: return 'C';
    case 2: return 'D';
    case 3: return 'H';
  }
}
