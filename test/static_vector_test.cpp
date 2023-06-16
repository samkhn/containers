#include "static_vector.hpp"

#include "gtest/gtest.h"

TEST(StaticVectorTest, Example) {
  SKTL::Containers::StaticVector<int, 4> v;
  v.PushBack(1);
  EXPECT_TRUE(v.Size() == 1);
}
