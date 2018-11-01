#include "card.hpp"

#include <iostream>
#include <string>

/// Return the suit shifted into its representation.
static inline unsigned
to_bits(Suit s)
{
  return static_cast<unsigned>(s) << 4;
}

/// Returns the rank as its representation.
static inline unsigned
to_bits(Rank r)
{
  return static_cast<unsigned>(r);
}

/// Returns the color as its representation.
static inline unsigned
to_bits(Color c)
{
  return static_cast<unsigned>(c);
}

/// Returns a number as its representation.
static inline unsigned
to_bits(int num)
{
  return static_cast<unsigned>(num);
}

static inline Suit
to_suit(unsigned n)
{
  return static_cast<Suit>(n >> 4);
}

static inline Rank
to_rank(unsigned n)
{
  return static_cast<Rank>(n & 0xf);
}
static inline Color
to_color(unsigned n)
{
  return static_cast<Color>(n >> 7);
}

Card::Card(Rank r, Suit s)
  : m_value(to_bits(s) | to_bits(r))
{
}

//Narrow contract
//precondition: 0 <= r <= 12 && 0 <= s <= 3
Card::Card(unsigned int r, unsigned int s)
  : m_value(s << 4 | r)
{
}

Rank
Card::get_rank() const
{
  return to_rank(m_value);
}

Suit
Card::get_suit() const
{
  return to_suit(m_value);
}

PlayingCard::PlayingCard(Card c)
  : m_value(to_bits(c.get_suit()) | to_bits(c.get_rank()))
{
}

PlayingCard::PlayingCard(Joker j)
  : m_value(to_bits(j.color) << 7 | to_bits(127))
{
}

bool
PlayingCard::is_normal() const
{
   return m_value < 127;
}

bool
PlayingCard::is_joker() const
{
  return m_value > 126;
}

Card
PlayingCard::get_normal()
{
  // Two things might be true: is_normal()
  // or is_joker().
  assert(is_normal());
  return Card(to_rank(m_value), to_suit(m_value));
}

Joker
PlayingCard::get_joker()
{
  assert(is_joker());
  return Joker(to_color(m_value));
}

CardKind
PlayingCard::get_kind() const
{
  if (m_value > 126)
    return JokerCard;
  return NormalCard;
}



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

bool
operator==(Card a, Card b)
{
  return a.get_raw_value() == b.get_raw_value();
}

bool
operator!=(Card a, Card b)
{
  return !(a == b);
}


bool
operator<(Card a, Card b)
{
  return a.get_raw_value() < b.get_raw_value();
}

bool
operator>(Card a, Card b)
{
  return b < a;
}

bool
operator<=(Card a, Card b)
{
  return !(b < a);
}

bool
operator>=(Card a, Card b)
{
  return !(a < b);
}

bool
operator==(PlayingCard a, PlayingCard b)
{
  return a.get_normal().get_rank() == b.get_normal().get_rank();
}

bool
operator!=(PlayingCard a, PlayingCard b)
{
  return !(a == b);
}


bool
operator<(PlayingCard a, PlayingCard b)
{
  return a.get_normal().get_rank() < b.get_normal().get_rank();
}

bool
operator>(PlayingCard a, PlayingCard b)
{
  return b < a;
}

bool
operator<=(PlayingCard a, PlayingCard b)
{
  return !(b < a);
}

bool
operator>=(PlayingCard a, PlayingCard b)
{
  return !(a < b);
}


std::ostream&
operator<<(std::ostream& os, Card c)
{
  return os << c.get_rank() << c.get_suit();
}

std::istream& operator>>(std::istream& is, Rank& r)
{
  char rank;
  is >> rank;
  switch (rank) {
  case 'a':
  case 'A': r = Ace;
       break;
  case '2': r = Two;
       break;
  case '3': r = Three;
       break;
  case '4': r = Four;
       break;
  case '5': r = Five;
       break;
  case '6': r = Six;
       break;
  case '7': r = Seven;
       break;
  case '8': r = Eight;
       break;
  case '9': r = Nine;
       break;
  case 't':
  case 'T': r = Ten;
       break;
  case 'j':
  case 'J': r = Jack;
       break;
  case 'q':
  case 'Q': r = Queen;
       break;
  case 'k':
  case 'K': r = King;
       break;
  default:
       is.setstate(std::ios_base::failbit);
       break;
  }
  return is;
}
std::istream& operator>>(std::istream& is, Suit& s)
{
  char suit;
  is >> suit;
  switch (suit)
  {
  case 's':
  case 'S': s = Spades;
        break;
  case 'c':
  case 'C': s = Clubs;
       break;
  case 'd':
  case 'D': s = Diamonds;
       break;
  case 'h':
  case 'H': s = Hearts;
       break;
  default:
       is.setstate(std::ios_base::failbit);
       break;
  }
  return is;
}

std::istream& operator>>(std::istream& is, Card& c)
{
  Rank r;
  Suit s;
  is >> r >> s;
  c.m_value = (to_bits(r) | to_bits(s));
  return is;
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
operator<<(std::ostream& os, Joker j)
{
  return os << j.color;
}
