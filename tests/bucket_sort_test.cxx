#include <bucket_sort.hxx>

#include "test.hxx"

namespace {

class BucketSortTest
: public Test {
protected:
  BucketSortTest()
  : sorter_()
  {}

  BucketSort const sorter_;
};

}

TEST_F(BucketSortTest, perform) {
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

  {
    std::vector<double> data{0.55, 0.50, 0.44, 0.40, 0.33, 0.30, 0.22, 0.20, 0.11, 0.10};
    sorter_.perform(data.begin(), data.end());
    EXPECT_EQ((std::vector<double>{0.10, 0.11, 0.20, 0.22, 0.30, 0.33, 0.40, 0.44, 0.50, 0.55}), data);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
  }
}
