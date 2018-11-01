
#include "card.hpp"
#include "poker.hpp"

#include <iostream>

int
main()
{
  std::array<PlayingCard, 5> h1 {Card{King, Diamonds},
                                 Card{Queen, Diamonds},
                                 Card{Ace, Diamonds},
                                 Card{Ten, Diamonds},
                                 Card{Jack, Diamonds}};
  std::cout << "Type in 5 cards, RankSuit, seperated by spaces(Ex: 2D TS AC...): ";
  for(auto& a : h1)
  {
    std::cin >> a;
  }


  Value pokerHand(h1);
  std::array<Rank, 5> h2 = pokerHand.get_cards();
  for (auto a : h2)
    std::cout << a << "\n";

  std::cout << "the hand is " << pokerHand.get_hand_type() << "\n";
}
