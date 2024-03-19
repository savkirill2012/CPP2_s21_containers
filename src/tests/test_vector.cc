#include <gtest/gtest.h>

#include <vector>

#include "main.h"

TEST(Vector, Constructors) {
  s21::vector<int> test;
  std::vector<int> test_v;

  ASSERT_EQ(test.size(), test_v.size());
  ASSERT_EQ(test.capacity(), test_v.capacity());
  ASSERT_EQ(test.data(), test_v.data());

  s21::vector<double> test1(10);
  std::vector<double> test_v1(10);

  ASSERT_EQ(test1.size(), test_v1.size());
  ASSERT_EQ(test1.capacity(), test_v1.capacity());

  s21::vector<double> test2{1, 2, 3};
  std::vector<double> test_v2{1, 2, 3};

  ASSERT_EQ(test2.size(), test_v2.size());
  ASSERT_EQ(test2.capacity(), test_v2.capacity());
  ASSERT_EQ(test2[0], test_v2[0]);
  ASSERT_EQ(test2[1], test_v2[1]);
  ASSERT_EQ(test2[2], test_v2[2]);

  s21::vector<double> test3 = test2;
  std::vector<double> test_v3 = test_v2;

  ASSERT_EQ(test3.size(), test_v3.size());
  ASSERT_EQ(test3.capacity(), test_v3.capacity());
  ASSERT_EQ(test3[0], test_v3[0]);
  ASSERT_EQ(test3[1], test_v3[1]);
  ASSERT_EQ(test3[2], test_v3[2]);

  s21::vector<double> test4(test2);
  std::vector<double> test_v4(test_v2);

  ASSERT_EQ(test4.size(), test_v4.size());
  ASSERT_EQ(test4.capacity(), test_v4.capacity());
  ASSERT_EQ(test4[0], test_v4[0]);
  ASSERT_EQ(test4[1], test_v4[1]);
  ASSERT_EQ(test4[2], test_v4[2]);
}

TEST(Vector, Metods) {
  s21::vector<double> test1{1, 2, 3};
  std::vector<double> test_v1{1, 2, 3};

  ASSERT_EQ(test1.at(2), test_v1.at(2));
  ASSERT_EQ(test1.front(), test_v1.front());
  ASSERT_EQ(test1.back(), test_v1.back());

  double* it = test1.data();
  double* it_v = test_v1.data();

  ASSERT_EQ(*it, *it_v);
  ASSERT_EQ(*(it + 1), *(it_v + 1));

  ASSERT_EQ(*(test1.begin()), *(test_v1.begin()));
  ASSERT_EQ(test1.size(), test_v1.size());
  ASSERT_EQ(test1.empty(), test_v1.empty());

  s21::vector<double> test2(10);
  std::vector<double> test_v2(10);

  ASSERT_EQ(test2.empty(), test_v2.empty());

  s21::vector<int> test;
  std::vector<int> test_v;

  ASSERT_EQ(test.empty(), test_v.empty());
  ASSERT_EQ(test2.max_size(), test_v2.max_size());
  ASSERT_EQ(test.max_size(), test_v.max_size());

  test.reserve(100);
  test_v.reserve(100);
  ASSERT_EQ(test.capacity(), test_v.capacity());

  test.shrink_to_fit();
  test_v.shrink_to_fit();
  ASSERT_EQ(test.capacity(), test_v.capacity());
  ASSERT_EQ(test1.at(1), test_v1.at(1));
  ASSERT_EQ(test1.at(2), test_v1.at(2));
  ASSERT_EQ(test1.size(), test_v1.size());
  ASSERT_EQ(test1.capacity(), test_v1.capacity());

  test1.erase(test1.begin() + 1);
  test_v1.erase(test_v1.begin() + 1);

  ASSERT_EQ(test1.size(), test_v1.size());
  ASSERT_EQ(test1.capacity(), test_v1.capacity());

  test1.push_back(32);
  test_v1.push_back(32);

  ASSERT_EQ(test1[2], test_v1[2]);
  ASSERT_EQ(test1.size(), test_v1.size());
  ASSERT_EQ(test1.capacity(), test_v1.capacity());

  test1.pop_back();
  test_v1.pop_back();

  ASSERT_EQ(test1[1], test_v1[1]);
  ASSERT_EQ(test1.size(), test_v1.size());
  ASSERT_EQ(test1.capacity(), test_v1.capacity());

  test1.clear();
  test_v1.clear();

  ASSERT_EQ(test1.size(), test_v1.size());
  ASSERT_EQ(test1.capacity(), test_v1.capacity());
}
