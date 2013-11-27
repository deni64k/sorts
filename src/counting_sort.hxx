#pragma once

#include <algorithm>
#include <memory>

#include "utils.hxx"

struct CountingSort {
  static char const description[];

  template <class BidirIt>
  void perform(BidirIt first, BidirIt last) const {
    if (last - first <= 1)
      return;

    auto const mm = std::minmax_element(first, last);
    auto const mi = *mm.first;
    auto const ma = *mm.second;
    auto const n  = ma - mi + 1;
    std::unique_ptr<unsigned[]> buckets(new unsigned[n]);
    std::fill(buckets.get(), buckets.get() + n, 0);

    for (BidirIt iter = first; iter != last; ++iter) {
      ++buckets[*iter - mi];
    }

    BidirIt  iter = first;
    unsigned i    = 0;
    while (i < n) {
      auto &bucket = buckets[i];

      if (bucket > 0) {
        *iter = i + mi;
        ++iter;
        --bucket;
      } else
        ++i;
    }
  }
};
