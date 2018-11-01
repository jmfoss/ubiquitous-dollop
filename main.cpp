
#include "card.hpp"
#include "poker.hpp"

#include <iostream>


void print(PlayingCard c)
{
  if (c.is_normal())
    std::cout << c.get_normal() << '\n';
  else
    std::cout << c.get_joker() << '\n';
}

int
main()
{
  std::array<PlayingCard, 5> h1 {Card{Jack, Hearts},
                                   Card{Queen, Hearts},
                                   Card{Two, Clubs},
                                   Card{Jack, Clubs},
                                   Card{Jack, Diamonds}};
  Value pokerHand(h1);
  std::array<Rank, 5> h2 = pokerHand.get_cards();
  for (auto a : h2)
    std::cout << a << "\n";

  std::cout << "the hand is " << pokerHand.get_hand_type() << "\n";
}
