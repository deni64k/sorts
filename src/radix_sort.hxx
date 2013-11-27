#pragma once

#include <unordered_map>
#include <algorithm>
#include <memory>

#include "quick_sort.hxx"
#include "insertion_sort.hxx"
#include "utils.hxx"

struct RadixSort {
  static char const description[];

  enum {n_digits = 10};

  // typedef int Digit;
  // static Digit get_digit(std::size_t const val, int const n) {
  //   return static_cast<Digit>(val / std::pow(10, n) % 10);
  // }
  // static Digit get_digit(char const *val, int const n) {
  //   return static_cast<Digit>(val + n);
  // }
  // static Digit get_digit(std::string const &val, int const n) {
  //   return static_cast<Digit>(val[n]);
  // }
  template <typename T>
  int get_digit(T const &n, int exp) const {
    return (n / exp) % 10;
  }

  template <class ForwardIt>
  void perform(ForwardIt first, ForwardIt last) const {
    typedef typename std::array<std::size_t, n_digits> Buckets;
    typedef typename std::iterator_traits<ForwardIt>::value_type IterData;

    auto const length = std::distance(first, last);

    if (length <= 1)
      return;

    auto const m = *std::max_element(first, last);
    Buckets buckets;
    int     exp = 1;
    std::vector<IterData> iters;
    iters.reserve(length);

    for (ForwardIt iter = first; iter != last; ++iter)
      iters.emplace_back(*iter);

    while (m / exp > 0) {
      for (auto &bucket : buckets)
        bucket = 0;

      ForwardIt iter = first, prev;
      prev = iter++;
      ++buckets[get_digit(*prev, exp)];
      for (std::size_t i = 1; i < length && iter != last; ++i, ++iter, ++prev)
        ++buckets[get_digit(*iter, exp)];

      for (std::size_t i = 1; i < buckets.size(); ++i)
        buckets[i] += buckets[i - 1];

      for (ForwardIt iter = last - 1; iter != first - 1; --iter)
        iters[--buckets[get_digit(*iter, exp)]] = *iter;

      auto iters_iter = iters.cbegin();
      for (iter = first; iter != last && iters_iter != iters.cend(); ++iter, ++iters_iter)
        *iter = *iters_iter;

      exp *= 10;
    }
  }

  // template <class ForwardIt>
  // void perform(ForwardIt first, ForwardIt last) const {
  //   typedef typename std::vector<ForwardIt> Bucket;
  //   typedef typename std::array<Bucket, 10> Buckets;
  //   typedef char                            Digit;
  //   typedef typename std::iterator_traits<ForwardIt>::value_type IterData;

  //   auto const length = std::distance(first, last);

  //   if (length <= 1)
  //     return;

  //   bool to_continue_sort = false;
  //   int  exp = 0, kk = 1;
  //   std::vector<ForwardIt> res;
  //   res.reserve(length);

  //   for (ForwardIt iter = first; iter != last; ++iter) {
  //     res.emplace_back(iter);
  //   }

  //   do {
  //     to_continue_sort = false;

  //     std::unique_ptr<Buckets> buckets_ptr(new Buckets());
  //     Buckets &buckets = *buckets_ptr;

  //     for (auto iter = res.begin(); iter != res.end(); ++iter) {
  //       auto const tmp = **iter / kk;
  //       Digit const digit = static_cast<Digit>(tmp % 10);
  //       to_continue_sort = to_continue_sort || tmp > 9;

  //       buckets[digit].emplace_back(*iter);
  //     }

  //     res.clear();
  //     for (int i = 0; i < buckets.size(); ++i) {
  //       auto const &bucket = buckets[i];
  //       for (auto iter = bucket.begin(); iter != bucket.end(); ++iter) {
  //         res.emplace_back(*iter);
  //       }
  //     }

  //     ++exp;
  //     kk *= 10;
  //   } while (to_continue_sort);

  //   std::vector<IterData> res_values;
  //   res_values.reserve(length);
  //   for (auto iter = res.begin(); iter != res.end(); ++iter) {
  //     res_values.emplace_back(**iter);
  //   }

  //   std::move(res_values.begin(), res_values.end(), first);
  // }
};
