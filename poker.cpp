#include "poker.hpp"
#include "card.hpp"
#include <algorithm>

// array sorted high card to low
Value::Value(std::array<PlayingCard, 5> &h)
  : m_hand(h)
{
  assert(h.size() == 5);
  unsigned type = 0;
  std::sort(m_hand.rbegin(), m_hand.rend());
  type = determineType();
  switch(type)
  {
    case 7: sortFourOfAKind();
      break;
    case 6: sortFullHouse();
      break;
    case 3: sortThreeOfAKind();
      break;
    case 2: sortTwoPair();
      break;
    case 1: sortOnePair();
      break;
  }
  m_value = ((type << 20) |
            (static_cast<unsigned>(m_hand[0].get_normal().get_rank()) << 16) |
            (static_cast<unsigned>(m_hand[1].get_normal().get_rank()) << 12) |
            (static_cast<unsigned>(m_hand[2].get_normal().get_rank()) << 8) |
            (static_cast<unsigned>(m_hand[3].get_normal().get_rank()) << 4) |
            (static_cast<unsigned>(m_hand[4].get_normal().get_rank()) << 0));
  //delete m_hand;
  return;
}

std::array<Rank, 5> Value::get_cards()
{
  return std::array<Rank, 5> {static_cast<Rank>((m_value >> 16) & 0xf),
                              static_cast<Rank>((m_value >> 12) & 0xf),
                              static_cast<Rank>((m_value >> 8) & 0xf),
                              static_cast<Rank>((m_value >> 4) & 0xf),
                              static_cast<Rank>((m_value >> 0) & 0xf)};
}

unsigned Value::determineType()
{
  if (isRoyalFlush()) return 9;
  if (isStraightFlush()) return 8;
  if (isFourOfAKind()) return 7;
  if (isFullHouse()) return 6;
  //if (isFlush()) return 5;
  if (isStraight()) return 4;
  if (isThreeOfAKind()) return 3;
  if (isTwoPair()) return 2;
  if (isOnePair()) return 1;
  return 0;
}

ValueKind Value::get_hand_type()
{
  return static_cast<ValueKind>(m_value >> 20);
}

void Value::sortFourOfAKind()
{
    if (m_hand[0].get_normal().get_rank() != m_hand[1].get_normal().get_rank())
    {                                                           // If the four of a kind are the last four cards
        swapCardsByIndex(0, 4);                                 // swap the first and last cards
    }                                                           // e.g. AS, 9D, 9H, 9S, 9C => 9C, 9D, 9H, 9S, AS
}

void Value::sortFullHouse()
{
    if (m_hand[0].get_normal().get_rank() != m_hand[2].get_normal().get_rank())
    {                                               // If the 3 of a kind cards are the last three
        swapCardsByIndex(0, 3);                     // swap cards 1 and 4, 2 and 5
        swapCardsByIndex(1, 4);                     // e.g. 10D, 10C, 6H, 6S, 6D => 6S, 6D, 6H, 10D, 10C
    }
}

void Value::sortThreeOfAKind()
{                                                                                       // If the 3 of a kind cards are the middle 3 cards
    if (m_hand[0].get_normal().get_rank() != m_hand[2].get_normal().get_rank() &&
        m_hand[4].get_normal().get_rank() != m_hand[3].get_normal().get_rank())
    {                                                                                   // swap cards 1 and 4
        swapCardsByIndex(0, 3);                                                         // e.g. AH, 8D, 8S, 8C, 7D => 8C, 8D, 8S, AH, 7D
    } else if (m_hand[0].get_normal().get_rank() != m_hand[2].get_normal().get_rank() &&
               m_hand[1].get_normal().get_rank() != m_hand[2].get_normal().get_rank())
    {
      swapCardsByIndex(0, 3);                                                          // swap cards 1 and 4, 2 and 5
      swapCardsByIndex(1, 4);
    }
}

void Value::sortTwoPair()
{
    if (m_hand[0].get_normal().get_rank() != m_hand[1].get_normal().get_rank())
    {                                                                        // If the two pairs are the last 4 cards
        for (int i = 0; i < 4; i++) {                                        // "bubble" the first card to the end
            swapCardsByIndex(i, i + 1);                                      // e.g. AH, 7D, 7S, 6H, 6C => 7D, 7S, 6H, 6C, AH
        }
    } else if (m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() &&
               m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank())
    {                                                                       // If the two pairs are the first and last two cards
        swapCardsByIndex(2, 4);                                             // swap the middle and last card
    }                                                                       // e.g. JS, JC, 8D, 4H, 4S => JS, JC, 4S, 4H, 8D
}

void Value::sortOnePair()
{                                                                    // If the pair are cards 2 and 3, swap cards 1 and 3
    if (m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank())
    {                                                                // e.g QD, 8H, 8C, 6S, 4J => 8C, 8H, QD, 6S, 4J
        swapCardsByIndex(0, 2);
    } else if (m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank())
    {                                                                // If the pair are cards 3 and 4, swap 1 and 3, 2 and 4
        swapCardsByIndex(0, 2);                                      // e.g. 10S, 8D, 4C, 4H, 2H => 4C, 4H, 10S, 8D, 2H
        swapCardsByIndex(1, 3);
    } else if (m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank())
    {                                                                // If the pair are the last 2 cards, reverse the order
        swapCardsByIndex(0, 2);
        swapCardsByIndex(1, 3);                                      // and then swap cards 3 and 5
        swapCardsByIndex(0, 4);                                      // e.g. 9H, 7D, 6C, 3D, 3S => 3S, 3D, 6C, 7D, 9H => 3S, 3D, 9H, 7D, 6C
    }
}

void Value::swapCardsByIndex(int index1, int index2)
{
    PlayingCard temp = m_hand[index1];
    m_hand[index1] = m_hand[index2];
    m_hand[index2] = temp;
}
bool Value::isRoyalFlush()
{
  return (isStraight() && isFlush() && m_hand[0].get_normal().get_rank() == Ace);
}

bool Value::isStraightFlush()
{
  return isStraight() && isFlush();
}

bool Value::isFourOfAKind()
{
    bool upper, lower;
    upper = m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() &&
         m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank() &&
         m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank();
    lower = m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank() &&
         m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank() &&
         m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank();

    return( upper || lower );
}

bool Value::isFullHouse()
{
  bool upper, lower;

      //Check for: x x x y y
      upper = m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() &&
           m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank() &&
           m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank();

      //Check for: x x y y y
      lower = m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() &&
           m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank() &&
           m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank();

      return( upper || lower );
}

bool Value::isFlush()
{
  int i, j, min_j;
      for ( i = 0 ; i < 5 ; i ++ )
      {
         min_j = i;

         for ( j = i+1 ; j < 5 ; j++ )
         {
            if ( m_hand[j].get_normal().get_suit() < m_hand[min_j].get_normal().get_suit() )
            {
               min_j = j;
            }
         }
         PlayingCard help = m_hand[i];
         m_hand[i] = m_hand[min_j];
         m_hand[min_j] = help;
      }
  return( m_hand[0].get_normal().get_suit() == m_hand[4].get_normal().get_suit());
}

bool Value::isStraight()
{
  int testRank = 0;
         testRank = m_hand[4].get_normal().get_rank() + 1;
         for (int i = 3; i > -1; --i )
         {
            if ( m_hand[i].get_normal().get_rank() != testRank )
               return false;        // Straight failed...

            ++testRank;   // Next card in hand
         }

         return true;        // Straight found !
}

bool Value::isThreeOfAKind()
{
  bool upper, middle, lower;

     //Check for: x x x a b
  upper = m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() &&
       m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank() ;

     //Check for: a x x x b
  middle = m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank() &&
       m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank() ;

     //Check for: a b x x x
  lower = m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank() &&
       m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank() ;

  return( upper || middle || lower );
}

bool Value::isTwoPair()
{
  bool upper, middle, lower;

     //Checking: a a  b b x
     upper = m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() &&
          m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank() ;

     //Checking: a a x  b b
     middle = m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() &&
          m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank() ;

     //Checking: x a a  b b
     lower = m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank() &&
          m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank() ;

     return( upper || middle || lower );
}

bool Value::isOnePair()
{
  bool upper, midUpper, midLower, lower;

      //Checking: a a x y z
      upper = m_hand[0].get_normal().get_rank() == m_hand[1].get_normal().get_rank() ;

      //Checking: x a a y z
      midUpper = m_hand[1].get_normal().get_rank() == m_hand[2].get_normal().get_rank() ;

      //Checking: x y a a z
      midLower = m_hand[2].get_normal().get_rank() == m_hand[3].get_normal().get_rank() ;

      //Checking: x y z a a
      lower = m_hand[3].get_normal().get_rank() == m_hand[4].get_normal().get_rank() ;

      return( upper || midUpper || midLower || lower );
}



bool operator==(Value& a, Value& b)
{
  return a.get_raw_value() == b.get_raw_value();
}

bool operator!=(Value& a, Value& b)
{
  return !(a == b);
}

bool operator<(Value& a, Value& b)
{
  return a.get_raw_value() < b.get_raw_value();
}

bool operator>(Value& a, Value& b)
{
  return b < a;
}

bool operator<=(Value& a, Value& b)
{
  return !(b < a);
}

bool operator>=(Value& a, Value& b)
{
  return !(a < b);
}

std::ostream&
operator<<(std::ostream& os, ValueKind k)
{
  switch (k) {
  case high: return os << "High Card";
  case two_kind: return os << "Two of a kind";
  case two_pair: return os << "Two pair";
  case three_kind: return os << "Three of a kind";
  case straight: return os << "Straight";
  case flush: return os << "Flush";
  case full_house: return os << "Full house";
  case four_kind: return os << "Four of a kind";
  case straight_flush: return os << "Straight Flush";
  case royal_flush: return os << "Royal Flush";
  }
}
