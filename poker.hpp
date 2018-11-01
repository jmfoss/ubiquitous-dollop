#include "card.hpp"
#include <array>

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

class Value
{
private:
  unsigned m_value;
  std::array<PlayingCard, 5> m_hand;
  unsigned determineType();
  bool isRoyalFlush();
  bool isStraightFlush();
  bool isFourOfAKind();
  bool isFullHouse();
  bool isFlush();
  bool isStraight();
  bool isThreeOfAKind();
  bool isTwoPair();
  bool isOnePair();
  void sortFourOfAKind();
  void sortFullHouse();
  void sortThreeOfAKind();
  void sortTwoPair();
  void sortOnePair();
  void swapCardsByIndex(int a, int b);

public:
  Value(std::array<PlayingCard, 5> &h);
  unsigned get_raw_value() { return m_value; }
  std::array<Rank, 5> get_cards();
  ValueKind get_hand_type();

};
