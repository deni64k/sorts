#pragma once

#include <unordered_map>
#include <algorithm>
#include <memory>
#include <type_traits>

#include "quick_sort.hxx"
#include "insertion_sort.hxx"
#include "utils.hxx"

struct RadixSort {
  static char const description[];

  static constexpr int n_digits = 10;

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

  template <typename T>
  int get_digit(T const &n, double exp) const {
    return static_cast<int>(n / exp) % 10;
  }

  template <typename ForwardIt>
  typename std::enable_if<std::is_integral<typename std::iterator_traits<ForwardIt>::value_type>::value>::type
  perform(ForwardIt first, ForwardIt last) const {
    typedef typename std::array<std::int_fast8_t, n_digits> Buckets;
    typedef typename std::iterator_traits<ForwardIt>::value_type IterData;

    auto const length = std::distance(first, last);

    if (length <= 1)
      return;

    auto const m = *std::max_element(first, last);
    Buckets buckets;
    int     exp = 1;
    std::vector<IterData> iters(first, last);

    while (m / exp > 0) {
      std::fill(buckets.begin(), buckets.end(), 0);

      ForwardIt iter = first, prev;
      prev = iter++;
      ++buckets[get_digit(*prev, exp)];
      for (std::size_t i = 1; i < length && iter != last; ++i, ++iter, ++prev)
        ++buckets[get_digit(*iter, exp)];

      for (std::size_t i = 1; i < buckets.size(); ++i)
        buckets[i] += buckets[i - 1];

      for (ForwardIt iter = last - 1; iter != first - 1; --iter)
        iters[--buckets[get_digit(*iter, exp)]] = *iter;

      std::move(iters.begin(), iters.end(), first);

      exp *= 10;
    }
  }

  template <class ForwardIt>
  typename std::enable_if<std::is_floating_point<typename std::iterator_traits<ForwardIt>::value_type>::value>::type
  perform(ForwardIt first, ForwardIt last) const
  {
    typedef typename std::array<std::int_fast8_t, n_digits> Buckets;
    typedef typename std::iterator_traits<ForwardIt>::value_type IterData;

    auto const length = std::distance(first, last);

    if (length <= 1)
      return;

    auto const m   = *std::max_element(first, last);
    auto       exp = m * 1e-9;
    Buckets               buckets;
    std::vector<IterData> iters(first, last);

    while (m / exp > 0) {
      std::fill(buckets.begin(), buckets.end(), 0);

      ForwardIt iter = first, prev;
      prev = iter++;
      ++buckets[get_digit(*prev, exp)];
      for (std::size_t i = 1; i < length && iter != last; ++i, ++iter, ++prev)
        ++buckets[get_digit(*iter, exp)];

      for (std::size_t i = 1; i < buckets.size(); ++i)
        buckets[i] += buckets[i - 1];

      for (ForwardIt iter = last - 1; iter != first - 1; --iter)
        iters[--buckets[get_digit(*iter, exp)]] = *iter;

      std::move(iters.begin(), iters.end(), first);

      exp *= 10;
    }
  }

  template <class ForwardIt>
  typename std::enable_if<utils::is_string<typename std::iterator_traits<ForwardIt>::value_type>::value>::type
  perform(ForwardIt first, ForwardIt last) const
  {
  }

  // template <typename ForwardIt, typename Char>
  // typename std::enable_if<std::is_base_of<typename std::iterator_traits<ForwardIt>::value_type, std::base_string<Char>>::value>::type
  // perform(ForwardIt first, ForwardIt last) const {
  //   perform()
  // }

  // template <class ForwardIt>
  // void
  // perform(ForwardIt first, ForwardIt last) const {
  //   static_assert(false, "Radix sort is not implemented for this type.");
  // }
};
