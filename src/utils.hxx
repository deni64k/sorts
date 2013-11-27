#pragma once

#include <iostream>
#include <iomanip>

#define DEBUG(x) // { std::cout << __PRETTY_FUNCTION__ << ":" << std::setw(6) << __LINE__ << " " << x; }

template <typename Value>
struct SimpleDataPrinter {
  void operator () (Value const &value) const {
    std::cout << value;
  }
};

template <class BidirIt, class Printer = SimpleDataPrinter<typename std::iterator_traits<BidirIt>::value_type>>
void print_data(BidirIt first, BidirIt last, Printer const &printer = Printer()) {
  for (; first != last; ++first) {
    printer(*first);
    std::cout << " ";
  }
  std::cout << std::endl;
}

template <class Container, class Printer = SimpleDataPrinter<typename std::iterator_traits<typename Container::iterator>::value_type>>
void print_data(Container const &data, Printer const &printer = Printer()) {
  print_data(data.begin(), data.end(), printer);
}
