#include "main.h"

//--------------------- LIST ----------------------
TEST(List, ConstructorDefault) {
  s21::list<int> s21List;
  std::list<int> stdList;
  EXPECT_EQ(s21List.empty(), stdList.empty());
}

TEST(List, Constructor_Size) {
  s21::list<int> s21List(8);
  std::list<int> stdList(8);
  EXPECT_EQ(s21List.size(), stdList.size());
  EXPECT_EQ(s21List.max_size(), stdList.max_size());
}

TEST(List, ConstructorList) {
  s21::list<int> s21List = {5, 6, 7};
  std::list<int> stdList = {5, 6, 7};
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
}

TEST(List, ConstructorCopy) {
  s21::list<int> s21List = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  s21::list<int> s21Copy(s21List);
  std::list<int> stdCopy(stdList);
  EXPECT_EQ(s21Copy.front(), stdCopy.front());
  EXPECT_EQ(s21Copy.back(), stdCopy.back());
}

TEST(List, OperatorCopy) {
  s21::list<int> s21List = {8, 9, 10};
  std::list<int> stdList = {8, 9, 10};
  s21::list<int> s21Copy(s21List);
  std::list<int> stdCopy;
  stdCopy = stdList;
  EXPECT_EQ(s21Copy.front(), stdCopy.front());
  EXPECT_EQ(s21Copy.back(), stdCopy.back());
}

TEST(List, ConstructorMove) {
  s21::list<int> s21List = {5, 6, 7};
  std::list<int> stdList = {5, 6, 7};
  s21::list<int> s21Copy(std::move(s21List));
  std::list<int> stdCopy(std::move(stdList));
  EXPECT_EQ(s21Copy.front(), stdCopy.front());
  EXPECT_EQ(s21Copy.back(), stdCopy.back());
  EXPECT_EQ(s21List.empty(), stdList.empty());
}

TEST(List, OperatorMove) {
  s21::list<int> s21List = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  s21::list<int> s21Copy;
  s21Copy = std::move(s21List);
  std::list<int> stdCopy;
  stdCopy = std::move(stdList);
  EXPECT_EQ(s21Copy.front(), stdCopy.front());
  EXPECT_EQ(s21Copy.back(), stdCopy.back());
  EXPECT_EQ(s21List.empty(), stdList.empty());
}

TEST(List, Size) {
  s21::list<int> s21List = {7, 8, 9};
  std::list<int> stdList = {7, 8, 9};
  EXPECT_EQ(s21List.size(), stdList.size());
}

TEST(List, PushFront) {
  s21::list<int> s21List;
  std::list<int> stdList;
  s21List.push_front(1);
  stdList.push_front(1);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_front(2);
  stdList.push_front(2);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_front(3);
  stdList.push_front(3);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
}

TEST(List, PushBack) {
  s21::list<int> s21List;
  std::list<int> stdList;
  s21List.push_back(1);
  stdList.push_back(1);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_back(2);
  stdList.push_back(2);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_back(3);
  stdList.push_back(3);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
}

TEST(List, PopFront) {
  s21::list<int> s21List;
  std::list<int> stdList;
  s21::list<int> s21List_;
  s21List.push_back(1);
  stdList.push_back(1);
  EXPECT_THROW(s21List_.pop_front(), std::out_of_range);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_back(2);
  stdList.push_back(2);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_back(3);
  stdList.push_back(3);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.pop_front();
  stdList.pop_front();
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
}

TEST(List, PopBack) {
  s21::list<int> s21List__;
  s21::list<int> s21List;
  std::list<int> stdList;
  s21::list<int> s21List_ = {8};
  s21List.push_back(1);
  stdList.push_back(1);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_back(2);
  stdList.push_back(2);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.push_back(3);
  stdList.push_back(3);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List_.pop_back();
  s21List.pop_back();
  stdList.pop_back();
  EXPECT_THROW(s21List__.pop_back(), std::out_of_range);
  EXPECT_EQ(s21List_.empty(), 1);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
}

TEST(List, IteratorBegin) {
  s21::list<int> s21List = {8, 9, 10};
  std::list<int> stdList = {8, 9, 10};
  s21::list<int>::iterator s21It;
  s21It = s21List.begin();
  std::list<int>::iterator stdIt;
  stdIt = stdList.begin();
  EXPECT_EQ(*s21It, *stdIt);
}

TEST(List, IteratorBeginPlusAndMinus) {
  s21::list<int> s21List = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  s21::list<int>::iterator s21It;
  s21It = s21List.begin();
  ++s21It;
  std::list<int>::iterator stdIt;
  stdIt = stdList.begin();
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
  --s21It;
  --stdIt;
  EXPECT_EQ(*s21It, *stdIt);
}

TEST(List, ConstIteratorBeginPlusAndMinus) {
  s21::list<int> s21List = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  s21::list<int>::const_iterator s21It;
  s21It = s21List.begin();
  ++s21It;
  std::list<int>::const_iterator stdIt;
  stdIt = stdList.begin();
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
  --s21It;
  --stdIt;
  EXPECT_EQ(*s21It, *stdIt);
}

TEST(List, IteratorEnd_Last) {
  s21::list<int> s21List = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  s21::list<int>::iterator s21It;
  s21It = s21List.end();
  std::list<int>::iterator stdIt;
  stdIt = stdList.end();
  EXPECT_EQ(*s21It, *stdIt);
}

TEST(List, ConstIteratorEnd_Last) {
  s21::list<int> s21List = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  s21::list<int>::const_iterator s21It;
  s21It = s21List.end();
  std::list<int>::const_iterator stdIt;
  stdIt = stdList.end();
  EXPECT_EQ(*s21It, *stdIt);
}

TEST(List, IteratorEquals) {
  s21::list<int> firstList = {1, 2, 3};
  s21::list<int>::iterator s21ItFirst;
  s21ItFirst = firstList.begin();
  s21::list<int>::iterator s21ItSecond;
  s21ItSecond = firstList.begin();
  EXPECT_TRUE(s21ItFirst == s21ItSecond);
  ++s21ItSecond;
  EXPECT_TRUE(s21ItFirst != s21ItSecond);
}

TEST(List, ConstIteratorEquals) {
  s21::list<int> firstList = {1, 2, 3};
  s21::list<int>::const_iterator s21ItFirst;
  s21ItFirst = firstList.begin();
  s21::list<int>::const_iterator s21ItSecond;
  s21ItSecond = firstList.begin();
  ++s21ItSecond;
  ++s21ItFirst;
  EXPECT_TRUE(s21ItFirst == s21ItSecond);
}

TEST(List, Insert) {
  s21::list<int> s21List;
  std::list<int> stdList;
  s21::list<int> s21List_;
  std::list<int> stdList_;
  s21::list<int>::iterator s21It;
  s21It = s21List.begin();
  std::list<int>::iterator stdIt;
  stdIt = stdList.begin();
  s21::list<int>::iterator s21It_;
  s21It_ = s21List_.end();
  std::list<int>::iterator stdIt_;
  stdIt_ = stdList_.end();
  s21List.insert(s21It, 5);
  stdList_.insert(stdIt_, 5);
  s21List_.insert(s21It_, 5);
  stdList.insert(stdIt, 5);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  EXPECT_EQ(s21List_.back(), stdList_.back());
  s21List.insert(s21It, 8);
  stdList.insert(stdIt, 8);
  s21List.insert(s21It, 9);
  stdList.insert(stdIt, 9);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  EXPECT_EQ(s21List.size(), stdList.size());
}

TEST(List, InsertWithConstIterator) {
  s21::list<int> s21List;
  std::list<int> stdList;
  s21::list<int>::const_iterator s21It;
  s21It = s21List.begin();
  std::list<int>::const_iterator stdIt;
  stdIt = stdList.begin();
  s21List.insert(s21It, 5);
  stdList.insert(stdIt, 5);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21List.insert(s21It, 8);
  stdList.insert(stdIt, 8);
  s21List.insert(s21It, 9);
  stdList.insert(stdIt, 9);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  EXPECT_EQ(s21List.size(), stdList.size());
}

TEST(List, Erase) {
  s21::list<int> s21List_;
  s21::list<int> s21List = {2, 1, 3, 4, 5};
  std::list<int> stdList = {2, 1, 3, 4, 5};
  s21List.erase(s21List.begin());
  stdList.erase(stdList.begin());
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
  s21::list<int>::iterator s21It;
  s21It = s21List.begin();
  ++s21It;
  std::list<int>::iterator stdIt;
  stdIt = stdList.begin();
  ++stdIt;
  EXPECT_THROW(s21List_.erase(s21List_.begin()), std::invalid_argument);
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
}

TEST(List, Splice) {
  s21::list<int> s21tmp;
  s21::list<int> s21List(s21tmp);
  s21::list<int> s21List_ = {3, 8};
  s21::list<int> s21ListFirst = {2};
  s21::list<int> s21ListSecond = {1, 3, 4, 5};
  std::list<int> stdListFirst = {2};
  std::list<int> stdListSecond = {1, 3, 4, 5};
  s21::list<int>::iterator s21It = s21ListFirst.begin();
  std::list<int>::iterator stdIt = stdListFirst.begin();
  s21::list<int>::iterator s21ItEnd = s21List.end();
  s21List.splice(s21ItEnd, s21List_);
  s21ListFirst.splice(s21It, s21ListSecond);
  stdListFirst.splice(stdIt, stdListSecond);
  EXPECT_EQ(s21List.front(), 3);
  EXPECT_EQ(s21List.back(), 8);
  EXPECT_EQ(s21ListFirst.front(), stdListFirst.front());
  EXPECT_EQ(s21ListFirst.back(), stdListFirst.back());
  EXPECT_EQ(s21ListFirst.size(), stdListFirst.size());
}

TEST(List, Merge) {
  s21::list<int> s21ListFirst = {2};
  s21::list<int> s21ListSecond = {1, 3, 4, 5};
  std::list<int> stdListFirst = {2};
  std::list<int> stdListSecond = {1, 3, 4, 5};
  s21ListFirst.merge(s21ListSecond);
  stdListFirst.merge(stdListSecond);
  EXPECT_EQ(s21ListFirst.front(), stdListFirst.front());
  EXPECT_EQ(s21ListFirst.back(), stdListFirst.back());
  EXPECT_EQ(s21ListSecond.empty(), stdListSecond.empty());
  EXPECT_EQ(s21ListSecond.size(), stdListSecond.size());
  s21::list<int> s21ListFirst_;
  std::list<int> stdListFirst_;
  s21ListSecond = {1, 3, 4, 5};
  stdListSecond = {1, 3, 4, 5};
  s21ListFirst_.merge(s21ListSecond);
  stdListFirst_.merge(stdListSecond);
  EXPECT_EQ(s21ListFirst_.front(), stdListFirst_.front());
  EXPECT_EQ(s21ListFirst_.back(), stdListFirst_.back());
  EXPECT_EQ(s21ListSecond.empty(), stdListSecond.empty());
  EXPECT_EQ(s21ListSecond.size(), stdListSecond.size());
}

TEST(List, Reverse) {
  s21::list<int> s21List = {1, 2, 3, 4, 5};
  std::list<int> stdList = {1, 2, 3, 4, 5};
  s21List.reverse();
  stdList.reverse();
  EXPECT_EQ(s21List.front(), stdList.front());
  EXPECT_EQ(s21List.back(), stdList.back());
}

TEST(List, Unique) {
  s21::list<int> s21List = {1, 1, 2, 2, 3, 3};
  std::list<int> stdList = {1, 1, 2, 2, 3, 3};
  s21::list<int>::iterator s21It;
  std::list<int>::iterator stdIt;
  s21List.unique();
  stdList.unique();
  s21It = s21List.begin();
  stdIt = stdList.begin();
  EXPECT_EQ(*s21It, *stdIt);
  ++s21It;
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
  ++s21It;
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
}

TEST(List, Sort) {
  s21::list<int> s21List = {2, 5, 1, 3, 8};
  std::list<int> stdList = {2, 5, 1, 3, 8};
  s21::list<int>::iterator s21It;
  std::list<int>::iterator stdIt;
  s21List.sort();
  stdList.sort();
  s21It = s21List.begin();
  stdIt = stdList.begin();
  EXPECT_EQ(*s21It, *stdIt);
  ++s21It;
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
  ++s21It;
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
  ++s21It;
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
  ++s21It;
  ++stdIt;
  EXPECT_EQ(*s21It, *stdIt);
}

TEST(List, InsertMany) {
  s21::list<int> s21List = {1, 2, 3, 4, 5};
  s21::list<int>::iterator s21It = s21List.begin();
  ++s21It;
  s21List.insert_many(s21It, 7, 8, 9);
  s21It = s21List.begin();
  EXPECT_EQ(*s21It, 1);
  ++s21It;
  EXPECT_EQ(*s21It, 7);
  ++s21It;
  EXPECT_EQ(*s21It, 8);
  ++s21It;
  EXPECT_EQ(*s21It, 9);
  ++s21It;
  EXPECT_EQ(*s21It, 2);
}

TEST(List, InsertManyBack) {
  s21::list<int> s21List = {1, 2, 3, 4, 5};
  s21::list<int>::iterator s21It;
  s21List.insert_many_back(7, 8, 9);
  s21It = s21List.end();
  EXPECT_EQ(*s21It, 9);
  --s21It;
  EXPECT_EQ(*s21It, 8);
  --s21It;
  EXPECT_EQ(*s21It, 7);
  --s21It;
  EXPECT_EQ(*s21It, 5);
  --s21It;
  EXPECT_EQ(*s21It, 4);
}

TEST(List, InsertManyFront) {
  s21::list<int> s21List = {1, 2, 3, 4, 5};
  s21::list<int>::iterator s21It;
  s21List.insert_many_front(7, 8, 9);
  s21It = s21List.begin();
  EXPECT_EQ(*s21It, 9);
  ++s21It;
  EXPECT_EQ(*s21It, 8);
  ++s21It;
  EXPECT_EQ(*s21It, 7);
  ++s21It;
  EXPECT_EQ(*s21It, 1);
  ++s21It;
  EXPECT_EQ(*s21It, 2);
}
