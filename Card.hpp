#ifndef CARD_HPP
#define CARD_HPP

//enum that makes up suits
enum Suit
{
  Spades,
  Clubs,
  Diamonds,
  Hearts,
};

//enum that makes up ranks
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

class Card
{
public:
  Card() = default;
  Card(Rank r, Suit s);
  Rank get_rank const() { return m_rank; };
  Suit get_suit const() { return m_suit; };

private:
  Rank m_rank;
  Suit m_suit;
};

#endif CARD_HPP
