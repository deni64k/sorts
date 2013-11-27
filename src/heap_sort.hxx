#pragma once

#include <algorithm>

#include "utils.hxx"

// Example heap:
//                           96
//               85                        89
//       72              50          75         81
//   18     54       47     27    57    56    29  63
//  3 16  21 53    13  9  15  0 41  2

struct HeapSort {
  static char const description[];

  template <class BidirIt>
  void perform(BidirIt first, BidirIt last) const {
    if (last - first <= 1)
      return;

    build_heap(first, last);

    for (BidirIt iter = last - 1; iter != first; --iter) {
      std::swap(*iter, *first);
      heapify(first, iter, first);
    }
  }

  template <class BidirIt>
  void build_heap(BidirIt first, BidirIt last) const {
    for (BidirIt iter = first + (last - first) / 2 - 1; iter != first - 1; --iter) {
      heapify(first, last, iter);
    }
  }

  template <class BidirIt>
  void heapify(BidirIt first, BidirIt last, BidirIt node) const {
    if (last - first <= 1)
      return;

    BidirIt const left  = first + ((node - first + 1) * 2 - 1);
    BidirIt const right = first + ((node - first + 1) * 2);
    BidirIt       largest;

    if (last - left > 0 && *node < *left)
      largest = left;
    else
      largest = node;

    if (last - right > 0 && *largest < *right)
      largest = right;

    if (largest != node) {
      std::swap(*largest, *node);
      heapify(first, last, largest);
    }
  }
};
