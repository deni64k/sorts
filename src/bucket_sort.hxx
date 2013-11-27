#pragma once

#include <unordered_map>
#include <algorithm>
#include <memory>

#include "quick_sort.hxx"
#include "insertion_sort.hxx"
#include "utils.hxx"

struct BucketSort {
  static char const description[];

  typedef std::size_t HashKey;
  static HashKey hash_func(double const val) {
    return static_cast<int>(val * 10.0);
  }
  static HashKey hash_func(int const val) {
    return static_cast<int>(val / 100);
  }

  template <class Data>
  class Buckets
  : public std::unordered_map<HashKey, std::vector<Data>> {
  public:
    typedef std::vector<Data> Bucket;
  };

  template <class BidirIt>
  void perform(BidirIt first, BidirIt last) const {
    typedef typename std::iterator_traits<BidirIt>::value_type IterData;

    if (last - first <= 1)
      return;

    std::unique_ptr<Buckets<IterData>> buckets_ptr(new Buckets<IterData>());
    Buckets<IterData> &buckets = *buckets_ptr;

    for (BidirIt iter = first; iter != last; ++iter) {
      buckets[hash_func(*iter)].emplace_back(*iter);
    }

    std::vector<HashKey> keys;
    keys.reserve(buckets.size());
    for (auto const &pair : buckets) {
      keys.emplace_back(pair.first);
    }
    QuickSort().perform(keys.begin(), keys.end());

    BidirIt iter = first;
    for (auto const &key : keys) {
      auto &bucket = buckets.at(key);

      InsertionSort().perform(bucket.begin(), bucket.end());

      for (auto biter = bucket.cbegin(); biter != bucket.cend(); ++biter)
        *(iter++) = *biter;
    }
  }
};
