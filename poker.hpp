
#include "card.hpp"

// Values of a poker hand:
// - High card
// - Two
// - Two pair
// - Three
// - Straight (5 consecutive, ace plays both)
// - Flush (same color)
// - Full House
// - Four
// - Straight Flush

struct High
{
  // We need all 5 ranks since two hands might
  // have the same crappy hand.
  //
  // Must be sorted in order of rank.
  std::array<Rank, 5> ranks;
};

bool operator<(High a, High b)
{
  return a.ranks < b.ranks;
}

struct Two
{
  // The rank of the pair.
  Rank pair;

  // The sorted rank of remaining cards.
  std::array<Rank, 3> high;
};

struct TwoPair
{
  // The sorted ranks of pairs.
  std::array<Rank, 2> pairs;

  // The remaining high card.
  Rank high;
};

struct Three
{
  // The rank of the three-of-a-kind.
  Rank three;

  // Sorted high cards for tie breakers.
  std::array<Rank, 2>;
};

struct Straight
{
  // The rank of the highest card.
  Rank high;
};

struct Flush
{
  // High card for equal flushes wins.
  std::array<Rank, 5>;
};

struct FullHouse
{
  // Two ranks: the pair over the triple.
  std::array<Rank, 2>;
};

struct Four
{
  Rank rank;

  // NOTE: Not usually needed since you can't
  // have two equal four-of-a-kind values.
  Rank high;
};

struct StraightFlush
{
  // Just need the rank of the high card.
  Rank high;
};

// Discriminator for the values of a poker hand.
enum ValueKind
{
  high,
  two_kind,
  two_pair,
  three_kind,
  straight,
  flush,
  full_house,
  four_kind,
  straight_flush,
};

enum ValueData
{
  High high;
  Two two;
  TwoPair twice;
  Three three;
  Straight straight;
  Flush flush;
  FullHouse house;
  Four four;
  StraightFlush sf;
};

struct Value
{
  ValueKind k;
  ValueData d;
};

bool operator<(const Value& a, const Value& b)
{
  if (a.k < b.k)
    return true;
  if (b.k < a.k)
    return false;
  switch (a.k) {
  case high:
    return a.high < b.high;
  case two_kind:
  case two_pair:
  case three_kind:
  case straight:
  case flush:
  case full_house:
  case four_kind:
  case straight_flush:
  }
}
