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
  Ace,
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
struct Card {
  Rank rank;
  Suit suit;
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
  Color color;
};

// Or directly as a tuple.
// using Joker = std::tuple<Color>;

union CardData
{
  CardData(Card c) : card(c) { }
  CardData(Joker j) : joker(j) { }

  Card card;
  Joker joker;
};

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
  PlayingCard(Card c) 
    : m_kind(NormalCard), m_data(c) { }
  
  // If the value of the playing card is a joker,
  // the discriminator MUST be JokerCard.
  PlayingCard(Joker j)
    : m_kind(JokerCard), m_data(j) { }

  // Queries

  CardKind get_kind() const { return m_kind; }
  // Returns the kind of the card.

  bool is_normal() const { return m_kind == NormalCard; }
  // True if this is a normal.

  bool is_joker() const { return m_kind == JokerCard; }
  // True if this is a joker.

  // Accessors

  Card get_normal()
    // Returns the underlying normal card.
    // Behavior is undefined if is_normal() returns false.
  {
    // Two things might be true: is_normal()
    // or is_joker().
    assert(is_normal());
    return m_data.card;
  }

  Joker get_joker()
    // Returns the underlying normal card.
    // Behavior is undefined if is_joker() returns false.
  {
    assert(is_joker());
    return m_data.joker;
  }

private:
  CardKind m_kind;
  CardData m_data;
};

// using PlayingCard = std::variant<Card, Joker>;

std::ostream& operator<<(std::ostream& os, Rank r);
std::ostream& operator<<(std::ostream& os, Suit s);
std::ostream& operator<<(std::ostream& os, Color c);
std::ostream& operator<<(std::ostream& os, Card c);
std::ostream& operator<<(std::ostream& os, Joker j);
