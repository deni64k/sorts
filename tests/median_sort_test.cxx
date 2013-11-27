#include <median_sort.hxx>

#include "test.hxx"

namespace {

class MedianSortTest
: public Test {
protected:
  MedianSortTest()
  : sorter_()
  {}

  MedianSort const sorter_;
};

}

TEST_F(MedianSortTest, partition) {
  {
    std::vector<int> data{};
    sorter_.partition(data.begin(), data.end(), data.begin());
    EXPECT_EQ((std::vector<int>{}), data);
  }

  {
    std::vector<int> data{1};
    sorter_.partition(data.begin(), data.end(), data.begin());
    EXPECT_EQ((std::vector<int>{1}), data);
  }

  {
    std::vector<int> data{1, 2};
    sorter_.partition(data.begin(), data.end(), data.begin());
    EXPECT_EQ((std::vector<int>{1, 2}), data);
  }

  {
    std::vector<int> data{1, 2};
    sorter_.partition(data.begin(), data.end(), data.begin() + 1);
    EXPECT_EQ((std::vector<int>{1, 2}), data);
  }

  {
    std::vector<int> data{5, 4, 3, 2, 1};
    sorter_.partition(data.begin(), data.end(), data.begin() + 2);
    // 5 4 3 2 1
    //     ^   ^
    // 5 4 1 2 3
    // ^   ^
    // 1 4 5 2 3
    //   ^   ^
    // 1 2 5 4 3
    //     ^   ^
    // 1 2 3 4 5
    EXPECT_EQ((std::vector<int>{1, 2, 3, 4, 5}), data);
  }

  {
    std::vector<int> data{5, 4, 3, 2, 1};
    sorter_.partition(data.begin(), data.end(), data.begin() + 1);
    // 5 4 3 2 1
    //   ^     ^
    // 5 1 3 2 4
    // ^ ^
    // 1 5 3 2 4
    //   ^ ^
    // 1 3 5 2 4
    //     ^ ^
    // 1 3 2 5 4
    //       ^ ^
    // 1 3 2 4 5
    EXPECT_EQ((std::vector<int>{1, 3, 2, 4, 5}), data);
  }

  {
    std::vector<int> data{3, 4, 1};
    sorter_.partition(data.begin(), data.end(), data.begin());
    // 3 4 1
    // ^   ^
    // 1 4 3
    //   ^ ^
    // 1 3 4
    EXPECT_EQ((std::vector<int>{1, 3, 4}), data);
  }
}

TEST_F(MedianSortTest, find_median) {
  {
    std::vector<int> data{};
    auto median_iter = sorter_.find_median(data.begin(), data.end(), data.begin());
    EXPECT_EQ(data.end(), median_iter);
  }

  {
    std::vector<int> data{1};
    auto median_iter = sorter_.find_median(data.begin(), data.end(), data.begin());
    EXPECT_EQ(1, *median_iter);
    EXPECT_EQ(0, median_iter - data.begin());
  }

  {
    std::vector<int> data{5, 4, 3, 2, 1};
    auto median_iter = sorter_.find_median(data.begin(), data.end(), data.begin());
    EXPECT_EQ(3, *median_iter);
    EXPECT_EQ(2, median_iter - data.begin());
  }
}

TEST_F(MedianSortTest, perform) {
  {
    std::vector<int> data{};
    sorter_.perform(data.begin(), data.end());
    EXPECT_EQ((std::vector<int>{}), data);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
  }

  {
    std::vector<int> data{1};
    sorter_.perform(data.begin(), data.end());
    EXPECT_EQ((std::vector<int>{1}), data);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
  }

  {
    std::vector<int> data{5, 4, 3, 2, 1};
    sorter_.perform(data.begin(), data.end());
    EXPECT_EQ((std::vector<int>{1, 2, 3, 4, 5}), data);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
  }
}
