#pragma once

#include <algorithm>

#include "utils.hxx"

struct InsertionSort {
  static char const description[];

  template <class BidirIt>
  void perform(BidirIt first, BidirIt last) const {
    if (last - first <= 1)
      return;

    for (BidirIt iter = first + 1; iter != last; ++iter) {
      for (BidirIt iter0 = first; iter0 != iter; ++iter0) {
        if (*iter < *iter0) {
          auto const min_element = *iter;
          std::move_backward(iter0, iter, iter + 1);
          *iter0 = min_element;
          break;
        }
      }
    }
  }
};
