#pragma once

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <list>

#include "utils.hxx"
#include "insertion_sort.hxx"

struct MedianSort {
  static char const description[];

  template <class BidirIt>
  void perform(BidirIt first, BidirIt last) const {
    constexpr auto min_gap = 16;

    if (last - first < 2)
      return;

    if (last - first <= min_gap)
      InsertionSort().perform(first, last);
    else {
      auto median = find_median(first, last, first);

      perform(first, median + 1);
      perform(median + 1, last);
    }
  }

  template <class BidirIt>
  BidirIt find_median(BidirIt first, BidirIt last,
                      BidirIt pivot_iter) const {
    int const mid_pos = (last - first - 1) / 2;

    pivot_iter = partition(first, last, pivot_iter);

    if (pivot_iter - first == mid_pos)
      return pivot_iter;

    for (;;) {
      BidirIt f, l;
      if (pivot_iter - first <= mid_pos) {
        f = pivot_iter + 1;
        l = last;
      } else {
        f = first;
        l = pivot_iter + 1;
      }
      pivot_iter = partition(f, l, f);

      if (pivot_iter == l)
        return l;

      if (pivot_iter - first == mid_pos)
        return pivot_iter;
    }

    return pivot_iter;
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
