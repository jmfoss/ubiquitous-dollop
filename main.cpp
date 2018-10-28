
#include "card.hpp"

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
  PlayingCard sa {Card{Ace, Spades}};
  PlayingCard s2 {Card{Two, Spades}};
  PlayingCard jr {Joker{Red}};
  print(sa); // OK
  print(s2); // OK?
  print(jr); // OK?
}
