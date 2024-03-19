#include <gtest/gtest.h>

#include <set>

#include "main.h"

TEST(Multiset, Unit_tests) {
  s21::multiset<int> test;
  std::multiset<int> test_m;

  ASSERT_EQ(test.size(), test_m.size());
  ASSERT_EQ(test.empty(), test_m.empty());
  ASSERT_EQ(test.max_size(), test.max_size());

  s21::multiset<char> test1{'c', 'b', 'b', 'b', 'r', 't'};
  std::multiset<char> test1_m{'c', 'b', 'b', 'b', 'r', 't'};

  s21::multiset<char>::iterator start = test1.begin();
  std::multiset<char>::iterator start_m = test1_m.begin();
  std::multiset<char>::iterator end_m = test1_m.end();

  for (; start_m != end_m; ++start_m, ++start) {
    ASSERT_EQ(*start_m, *start);
  }

  s21::multiset<char> test2(test1);
  std::multiset<char> test2_m(test1_m);

  s21::multiset<char>::iterator start1 = test2.begin();
  s21::multiset<char>::iterator end1 = test2.end();
  std::multiset<char>::iterator start1_m = test2_m.begin();

  for (; start1 != end1; ++start1_m, ++start1) {
    ASSERT_EQ(*start1_m, *start1);
  }

  s21::multiset<char>::iterator st = test1.insert('a');
  std::multiset<char>::iterator st1 = test1_m.insert('a');

  for (; st1 != end_m; ++st, ++st1) {
    ASSERT_EQ(*st, *st1);
  }

  test1.erase(test1.find('b'));
  test1_m.erase(test1_m.find('b'));

  st1 = test1_m.begin();
  st = test1.begin();

  for (; st1 != end_m; ++st, ++st1) {
    ASSERT_EQ(*st, *st1);
  }

  s21::multiset<char> test3{'a', 'z', 'e', 'w'};
  std::multiset<char> test3_m{'a', 'z', 'e', 'w'};

  test2.swap(test3);
  test2_m.swap(test3_m);

  s21::multiset<char>::iterator start2 = test2.begin();
  s21::multiset<char>::iterator end2 = test2.end();
  std::multiset<char>::iterator start2_m = test2_m.begin();

  for (; start2 != end2; ++start2, ++start2_m) {
    ASSERT_EQ(*start2, *start2_m);
  }

  s21::multiset<char>::iterator start3 = test3.begin();
  s21::multiset<char>::iterator end3 = test3.end();
  std::multiset<char>::iterator start3_m = test3_m.begin();

  for (; start3 != end3; ++start3, ++start3_m) {
    ASSERT_EQ(*start3, *start3_m);
  }

  test2.merge(test3);
  test2_m.merge(test3_m);

  start2 = test2.begin();
  end2 = test2.end();
  start2_m = test2_m.begin();

  start3 = test3.begin();
  end3 = test3.end();
  start3_m = test3_m.begin();

  for (; start2 != end2; ++start2, ++start2_m) {
    ASSERT_EQ(*start2, *start2_m);
  }

  test2.clear();
  test2_m.clear();

  ASSERT_EQ(test2.empty(), test2_m.empty());

  s21::multiset<char> test4{'a', 'e', 'e', 'w'};
  std::multiset<char> test4_m{'a', 'e', 'e', 'w'};

  ASSERT_EQ(test4.contains('h'), 0);
  ASSERT_EQ(test4.contains('w'), 1);

  std::pair<std::multiset<char>::iterator, std::multiset<char>::iterator> t1_m =
      test4_m.equal_range('e');
  std::pair<s21::multiset<char>::iterator, s21::multiset<char>::iterator> t1 =
      test4.equal_range('e');

  ASSERT_EQ(*t1.first, *t1_m.first);
  ASSERT_EQ(*t1.second, *t1_m.second);

  ASSERT_EQ(*test4.lower_bound('u'), *test4_m.lower_bound('u'));
  ASSERT_EQ(*test4.lower_bound('e'), *test4_m.lower_bound('e'));
  ASSERT_EQ(*test4.upper_bound('b'), *test4_m.upper_bound('b'));
  ASSERT_EQ(*test4.upper_bound('e'), *test4_m.upper_bound('e'));

  ASSERT_EQ(test4.count('e'), test4_m.count('e'));
  ASSERT_EQ(test4.count('i'), test4_m.count('i'));

  s21::multiset<char> test6 = test3;
  test6 = test1;

  const s21::multiset<int> test7 = {5, 7, 6, 8};
  const std::multiset<int> test7_m = {5, 7, 6, 8};

  s21::multiset<int>::const_iterator start_i = test7.begin();
  s21::multiset<int>::const_iterator end_i = test7.end();
  std::multiset<int>::const_iterator start_im = test7_m.begin();

  for (; start_i != end_i; ++start_i, ++start_im) {
    ASSERT_EQ(*start_i, *start_im);
  }
}
