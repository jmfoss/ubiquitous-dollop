#include "war.hpp"
#include "stats.hpp"

#include <ctime>
#include <iostream>
#include <random>

int
main()
{
  std::random_device rd;

  unsigned seed = rd();
  std::default_random_engine rng(seed);
  Accumulator acc(seed);

  // unsigned seed = 0;
  // std::default_random_engine rng(seed);
  // Accumulator acc(seed);
  /*
  for (int i = 0; i < 10000; ++i) {
    War w(rng, &acc);
    w.play();
  }

  std::cout << acc.get_stats();
  */

  do
  {
    std::cin.clear();
    Card c;
    std::cout << "Input a Rank(A, 1, 2, ...) followed by a Suit:" << std::endl;
    std::cin >> c;
    if (!std::cin.fail())
    std::cout << c << std::endl;
    else
    std::cout << "Invalid Rank or Suit, please try again" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (std::cin.fail());
  bool inRange = true;
  do
  {
    std::cout << "Input two integers. One for Rank and one for Suit:" << std::endl;
    int r, s;
    std::cin >> r >> s;
    if (r >= 0  && r <= 12 && s >= 0 && s <= 3)
    {
      Card c(r, s);
      std::cout << c << std::endl;
      inRange = true;
    }
    else
    {
      std::cout << "Integers are out of range" << std::endl;
      inRange = false;
    }
  } while (!inRange);
  return 0;
}
