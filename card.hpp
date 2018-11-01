#pragma once

#include <iosfwd>
#include <cassert>

enum Suit
{
  Spades,
  Clubs,
  Diamonds,
  Hearts,
};

enum Rank
{
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace,
};

enum Color
{
  Black,
  Red,
};

// A card is a suit and rank. In functional
// languages (or in type theory), this is
// also the product type.
//
//    Card = Rank * Suit
//
// Values are (Ace, Spades), (Two, Spades), ... etc.
class Card
{
public:
  Card() = default;
  /// Constructs a card with indeterminate value.

  Card(Rank r, Suit s);
  /// Constructs a card with a rank and suit.
  Card(unsigned int r, unsigned int s);
  /// Constructs a card with a rank and suit using integers.
  Card(Color c);

  // Accessors

  Rank get_rank() const;
  // Returns the rank of the card.

  Suit get_suit() const;
  // Returns the suit of the card.

  unsigned char get_raw_value() const { return m_value; }
  // Returns the underlying representation.

  friend std::istream& operator>>(std::istream& is, Card& c);
  // Give istream operator access to m_value

private:
  unsigned char m_value;
};

// Direct encoding of a product type in C++.
// using Card = std::tuple<Rank, Suit>;

// A Joker is either red or black. This is
// a weird degenerate product type:
//
//    Joker = Color * 0 (the empty type)
//
// Values are (Black), (Red)
struct Joker {
  Joker(Color c) : color(c) {}
  Color color;
};

// Or directly as a tuple.
// using Joker = std::tuple<Color>;
/*
union CardData
{
  CardData(Card c) : card(c) { }
  CardData(Joker j) : joker(j) { }

  Card card;
  Joker joker;
};
*/
// Defines the type of the discriminator for
// the union of cards and jokers.
enum CardKind {
  NormalCard,
  JokerCard,
};

// Variant or sum type or discriminated union.
//
// Writing these classes is HARD. Prefer to
// use std::variant (or something similar) if
// you can.
class PlayingCard
{
public:
  // Importantly, establish an invariant.
  // If the value of the playing card is a normal
  // card, the discriminator MUST be NormalCard.
  PlayingCard(Card c);

  // If the value of the playing card is a joker,
  // the discriminator MUST be JokerCard.
  PlayingCard(Joker j);

  // Queries

  CardKind get_kind() const;
  // Returns the kind of the card.

  bool is_normal() const;
  // True if this is a normal.

  bool is_joker() const;
  // True if this is a joker.
  unsigned char get_raw_value() { return m_value; }
  // Accessors

  Card get_normal();
    // Returns the underlying normal card.
    // Behavior is undefined if is_normal() returns false.

  Joker get_joker();
    // Returns the underlying normal card.
    // Behavior is undefined if is_joker() returns false.

private:
  unsigned char m_value;
};

// using PlayingCard = std::variant<Card, Joker>;

bool operator==(Card a, Card b);
bool operator!=(Card a, Card b);
bool operator>(Card a, Card b);
bool operator<(Card a, Card b);
bool operator>=(Card a, Card b);
bool operator==(PlayingCard a, PlayingCard b);
bool operator!=(PlayingCard a, PlayingCard b);
bool operator>(PlayingCard a, PlayingCard b);
bool operator<(PlayingCard a, PlayingCard b);
bool operator>=(PlayingCard a, PlayingCard b);

std::ostream& operator<<(std::ostream& os, Rank r);
std::ostream& operator<<(std::ostream& os, Suit s);
std::ostream& operator<<(std::ostream& os, Color c);
std::ostream& operator<<(std::ostream& os, Card c);
std::ostream& operator<<(std::ostream& os, Joker j);
std::istream& operator>>(std::istream& is, PlayingCard& p);
