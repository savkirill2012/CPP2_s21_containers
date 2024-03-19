#include <map>
#include <string>

#include "main.h"

TEST(mapTest, Default) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.size(), size_t(0));
  EXPECT_TRUE(m.empty());
}

TEST(mapTest, InitializerList) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), size_t(3));
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_EQ(m.at(3), "three");
}

TEST(mapTest, CopyTest) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> copy_m(m);
  EXPECT_EQ(copy_m.size(), size_t(3));
  EXPECT_FALSE(copy_m.empty());
  EXPECT_EQ(copy_m.at(1), "one");
}

TEST(mapTest, InsertKeyValue) {
  s21::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(map.size(), size_t(1));
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(2, "two");
  EXPECT_EQ(map.size(), size_t(2));
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(mapTest, InsertPair) {
  s21::map<int, std::string> map;
  map.insert(std::make_pair(1, "one"));
  EXPECT_EQ(map.size(), size_t(1));
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(std::make_pair(2, "two"));
  EXPECT_EQ(map.size(), size_t(2));
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}
TEST(mapTest, InsertOrAssign) {
  s21::map<int, std::string> map;
  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(it1.GetPointer()->GetKey(), 1);
  EXPECT_EQ(it1.GetPointer()->GetValue(), "one");
  auto [it2, inserted2] = map.insert_or_assign(1, "ONE");
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(it2.GetPointer()->GetKey(), 1);
  EXPECT_EQ(it2.GetPointer()->GetValue(), "ONE");
  map.insert_or_assign(2, "two");
  map.insert_or_assign(3, "three");
  map.insert_or_assign(4, "four");
  map.insert_or_assign(5, "five");
  EXPECT_EQ(map.size(), size_t(5));
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}
TEST(mapTest, AtAndOperatorBrackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::out_of_range);
  map[4] = "four";
  EXPECT_EQ(map[4], "four");
  map[2] = "TWO";
  EXPECT_EQ(map[2], "TWO");
  const s21::map<int, std::string> map1 = {
      {1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map1.at(1), "one");
  EXPECT_THROW(map1.at(4), std::out_of_range);
}

TEST(mapTest, EmptyAndSize) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), size_t(0));

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), size_t(3));
  const s21::map<int, std::string> empty_map_const;
  EXPECT_TRUE(empty_map_const.empty());
  EXPECT_EQ(empty_map_const.size(), size_t(0));
}

TEST(mapTest, MaxSize) {
  s21::map<int, std::string> map;

  EXPECT_GT(map.max_size(), size_t(0));
}
TEST(mapTest, Erase) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});

  auto it1 = map.begin();
  map.erase(it1);
  EXPECT_EQ(map.size(), size_t(3));
  EXPECT_FALSE(map.contains(1));
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.swap(map2);

  EXPECT_EQ(map1.size(), size_t(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));

  EXPECT_EQ(map2.size(), size_t(2));
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(mapTest, Merge) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.merge(map2);

  EXPECT_EQ(map1.size(), size_t(4));
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
}

TEST(mapTest, Contains) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(mapTest, InsertMany) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}
