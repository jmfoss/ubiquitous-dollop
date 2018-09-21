#ifndef CARD_HPP
#define CARD_HPP

//enum that makes up suits
enum Suit
{
  Spades,
  Clubs,
  Diamonds,
  Hearts
};

//enum that makes up ranks
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
  Ace
};

class Card
{
public:
  Card() = default;
  Card(Rank r, Suit s);
  char get_rank() const { return m_rank; };
  char get_suit() const { return m_suit; };
  friend std::ostream& operator<<(std::ostream& os, Card card);
private:
  Rank m_rank;
  Suit m_suit;
};



#endif
