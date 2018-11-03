#include "card.hpp"
#include <iostream>
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
  royal_flush,
};



class PokerHand
{
private:
  unsigned m_value;
  //is there a way to delete this after construction?
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
  PokerHand(std::array<PlayingCard, 5> hand);
  unsigned get_raw_value() { return m_value; }
  std::array<Rank, 5> get_cards();
  ValueKind get_hand_type();

};

std::ostream&
operator<<(std::ostream& os, ValueKind c);

bool operator==(PokerHand& a, PokerHand& b);
bool operator!=(PokerHand& a, PokerHand& b);
bool operator>(PokerHand& a, PokerHand& b);
bool operator<(PokerHand& a, PokerHand& b);
bool operator>=(PokerHand& a, PokerHand& b);
