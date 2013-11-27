#pragma once

#include <algorithm>

#include "utils.hxx"

struct SelectionSort {
  static char const description[];

  template <class BidirIt>
  void perform(BidirIt first, BidirIt last) const {
    while (first != last) {
      auto min_element_iter = first;
      for (auto iter = first + 1; iter != last; ++iter) {
        if (*iter < *min_element_iter)
          min_element_iter = iter;
      }
      if (min_element_iter != first) {
        std::swap(*min_element_iter, *first);
      }
      ++first;
    }
  }
};
