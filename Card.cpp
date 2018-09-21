#include "Card.hpp"

Card::Card(Rank r, Suit s) : m_rank(r), m_suit(s)
{

}

char Card::get_rank() const
{
  switch (m_rank)
  {
    case 0: return 'A';
    case 1: return '2';
    case 2: return '3';
    case 3: return '4';
    case 4: return '5';
    case 5: return '6';
    case 6: return '7';
    case 7: return '8';
    case 8: return '9';
    case 9: return 'T';
    case 10: return 'J';
    case 11: return 'Q';
    case 12: return 'K';
  }

}

char Card::get_suit() const
{
  switch (m_suit)
  {
    case 0: return 'S';
    case 1: return 'C';
    case 2: return 'D';
    case 3: return 'H';
  }
}
