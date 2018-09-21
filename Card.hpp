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

private:
  Rank m_rank;
  Suit m_suit;
};

std::ostream& operator<<(std::ostream& os, const Rank& rank)
{
  switch (rank)
  {
    case 0: return os << "2";
    case 1: return os << "3";
    case 2: return os << "4";
    case 3: return os << "5";
    case 4: return os << "6";
    case 5: return os << "7";
    case 6: return os << "8";
    case 7: return os << "9";
    case 8: return os << "T";
    case 9: return os << "J";
    case 10: return os << "Q";
    case 11: return os << "K";
    case 12: return os << "A";

  }

}

std::ostream& operator<<(std::ostream& os, const Suit& suit)
{
  switch (suit)
  {
    case 0: return os << "S";
    case 1: return os << "C";
    case 2: return os << "D";
    case 3: return os << "H";
  }
}

#endif
