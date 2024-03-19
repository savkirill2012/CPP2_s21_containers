#include "main.h"

//--------------------- ARRAY ----------------------
TEST(Array, ConstructorDefault) {
  s21::array<int, 8> arr;
  EXPECT_TRUE(arr.size() == 8);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_TRUE(arr[i] == 0);
  }
}

TEST(Array, ConstructorInitList) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  EXPECT_EQ(arr.size(), static_cast<unsigned long>(5));

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }
}

TEST(Array, ConstructorCopy) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrCopy(arr);
  EXPECT_EQ(arrCopy.size(), static_cast<unsigned long>(5));

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(Array, ConstructorMove) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrMove(std::move(arr));
  EXPECT_EQ(arrMove.size(), static_cast<unsigned long>(5));

  for (size_t i = 0; i < arrMove.size(); ++i) {
    EXPECT_EQ(arrMove[i], static_cast<int>(i) + 1);
  }
}

TEST(Array, Begin) {
  s21::array<int, 5> arr = {8, 7, 3, 9, 5};
  auto it = arr.begin();
  EXPECT_EQ(*it, 8);

  *it = 11;
  EXPECT_EQ(arr[0], 11);
}

TEST(Array, Data) {
  s21::array<int, 5> arr = {8, 7, 3, 9, 5};
  std::array<int, 5> arr1 = {8, 7, 3, 9, 5};
  auto it = arr.data();
  auto it1 = arr1.data();
  EXPECT_EQ(*it, 8);
  EXPECT_EQ(*it, *it1);

  *it = 11;
  EXPECT_EQ(arr[0], 11);
}

TEST(Array, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.end();

  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(Array, At_Valid) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(Array, At_OutOfRange) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr.at(11), std::out_of_range);
}

TEST(Array, ConstAt_Valid) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(Array, ConstAt_OutOfRange) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr.at(11), std::out_of_range);
}

TEST(Array, Front) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(Array, Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(Array, ConstFront) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(Array, ConstBack) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(Array, Empty_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_FALSE(arr.empty());
}

TEST(Array, Empty_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(Array, Size_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), static_cast<unsigned long>(5));
}

TEST(Array, Size_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.size(), static_cast<unsigned long>(0));
}

TEST(Array, MaxSize) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), static_cast<unsigned long>(5));
}

TEST(Array, Swap) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1.swap(arr2);

  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }

  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], static_cast<int>(i) + 1);
  }
}

TEST(Array, Fill) {
  s21::array<int, 5> arr;
  arr.fill(11);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 11);
  }
}

TEST(Array, CopyOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = arr2;

  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(Array, MoveOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = std::move(arr2);

  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
}

TEST(Array, OperatorBracket) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }

  arr[2] = 10;
  EXPECT_EQ(arr[2], 10);
}
