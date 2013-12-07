#pragma once

#include <iostream>
#include <iomanip>

#define DEBUG(x) // { std::cout << __PRETTY_FUNCTION__ << ":" << std::setw(6) << __LINE__ << " " << x; }

namespace utils {

template <typename T>
struct is_string
: public std::integral_constant<bool, std::is_same<char *, typename std::decay<T>::type>::value
                                      || std::is_same<const char *, typename std::decay<T>::type>::value>
{};

}

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
