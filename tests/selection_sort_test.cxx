#include <selection_sort.hxx>

#include "test.hxx"

namespace {

class SelectionSortTest
: public Test {
protected:
  SelectionSortTest()
  : sorter_()
  {}

  SelectionSort const sorter_;
};

}

TEST_F(SelectionSortTest, perform) {
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
