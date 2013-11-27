#pragma once

#include <algorithm>

#include "insertion_sort.hxx"
#include "utils.hxx"

struct QuickSort {
  static char const description[];

  template <class BidirIt>
  void perform(BidirIt first, BidirIt last) const {
    constexpr auto min_gap = 16;

    if (last - first <= 1)
      return;

    if (last - first <= min_gap)
      InsertionSort().perform(first, last);
    else {
      auto pivot = first + select_pivot_index(first, last);
      pivot = partition(first, last, pivot);

      perform(first, pivot + 1);
      perform(pivot + 1, last);
    }
  }

  template <class BidirIt>
  std::size_t select_pivot_index(BidirIt first, BidirIt last) const {
    return (last - first - 1) / 2;
  }

  template <class BidirIt>
  BidirIt partition(BidirIt first, BidirIt last,
                    BidirIt pivot_iter) const {
    if (last - first <= 1) {
      return first;
    }

    auto const pivot = *pivot_iter;

    std::swap(*pivot_iter, *(last - 1));
    pivot_iter = last - 1;

    BidirIt store_iter = first;
    BidirIt iter       = first;
    while (iter != pivot_iter) {
      if (*iter < pivot) {
        std::swap(*iter, *store_iter);
        ++store_iter;
      }
      ++iter;
    }

    std::swap(*store_iter, *pivot_iter);
    pivot_iter = store_iter;

    return pivot_iter;
  }
};
