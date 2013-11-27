#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// #include <gperftools/profiler.h>

#include "insertion_sort.hxx"
#include "median_sort.hxx"
#include "quick_sort.hxx"
#include "selection_sort.hxx"
#include "heap_sort.hxx"
#include "counting_sort.hxx"
#include "bucket_sort.hxx"
#include "radix_sort.hxx"

char const InsertionSort::description[] = "Insertion sort";
char const MedianSort::description[]    = "Median sort";
char const QuickSort::description[]     = "Quick sort";
char const SelectionSort::description[] = "Selection sort";
char const HeapSort::description[]      = "Heap sort";
char const CountingSort::description[]  = "Counting sort";
char const BucketSort::description[]    = "Bucket sort";
char const RadixSort::description[]     = "Radix sort";

namespace {

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

template <class Container>
void print_data(Container data) {
  for (auto const &dattum : data) {
    std::cout << dattum << " ";
  }
  std::cout << std::endl;
}

std::initializer_list<int> make_integral_data() {
  return {5, 4, 3, 2, 1, 10, 9, 8, 7, 6};
}

std::vector<int> make_random_integral_data(std::size_t size) {
  std::uniform_int_distribution<> distribution(0, size);
  std::vector<int> result;//(size, [&]() -> int { return distribution(generator); });

  std::generate_n(std::back_inserter(result), size, [&]() { return distribution(generator); });

  return result;
}

std::vector<double> make_random_single_data(std::size_t size) {
  std::uniform_real_distribution<> distribution(0, size);
  std::vector<double> result;//(size, [&]() -> int { return distribution(generator); });

  std::generate_n(std::back_inserter(result), size, [&]() { return distribution(generator); });

  return result;
}

template <class Sorter>
void sort_integral_by(std::size_t size = 100 * 1024) {
  {
    std::vector<int> data = make_integral_data();

    std::cout << Sorter::description << std::endl;
    print_data(data);

    auto const time_begin = std::chrono::system_clock::now();
    Sorter().perform(data.begin(), data.end());

    print_data(data);
    std::cout << (std::is_sorted(data.begin(), data.end()) ? "OK " : "FAIL ")
              << std::setw(15) << data.size() << " elements, "
              << std::setw(15) << std::fixed << (std::chrono::system_clock::now() - time_begin).count() / 1e6 << " ms"
              << std::endl;
  }

  return;
  {
    auto data = make_random_integral_data(size);

    std::cout << Sorter::description << std::endl;
    // print_data(data);

    auto const time_begin = std::chrono::system_clock::now();

    // ProfilerStart((std::string(Sorter::description) + ".prof").c_str());
    Sorter().perform(data.begin(), data.end());
    // ProfilerStop();
    // ProfilerFlush();

    // print_data(data);
    std::cout << "OK "
              << std::setw(15) << data.size() << " elements, "
              << std::setw(15) << std::fixed << (std::chrono::system_clock::now() - time_begin).count() / 1e6 << " ms"
              << std::endl;
  }
}

}

int main(int argc, char const *argv[]) {
  sort_integral_by<InsertionSort>();
  sort_integral_by<MedianSort>(5 * 1024);
  sort_integral_by<QuickSort>();
  sort_integral_by<SelectionSort>(5 * 1024);
  sort_integral_by<HeapSort>();
  sort_integral_by<CountingSort>();
  sort_integral_by<BucketSort>();
  sort_integral_by<RadixSort>();

  return 0;
}
