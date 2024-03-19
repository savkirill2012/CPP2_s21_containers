#include <queue>

#include "main.h"

TEST(Queue, Defualt_Constructor) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(Queue, Constructor_InitList) {
  s21::queue<int> s21_queue_list{9, 8, 7};
  std::queue<int> std_queue_list;
  std_queue_list.push(9);
  std_queue_list.push(8);
  std_queue_list.push(7);

  EXPECT_EQ(s21_queue_list.size(), std_queue_list.size());
  EXPECT_EQ(s21_queue_list.front(), std_queue_list.front());
  EXPECT_EQ(s21_queue_list.back(), std_queue_list.back());
}

TEST(Queue, Copy_Constructor) {
  s21::queue<int> s21_queue = {1, 2, 3};
  s21::queue<int> s21_copy(s21_queue);
  std::queue<int> std_queue;

  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);

  std::queue<int> std_copy(std_queue);

  EXPECT_EQ(s21_copy.front(), std_copy.front());
  EXPECT_EQ(s21_copy.back(), std_copy.back());
}

TEST(Queue, Move_Constructor) {
  s21::queue<int> s21_queue = {1, 2, 3};
  s21::queue<int> s21_move(std::move(s21_queue));
  std::queue<int> std_queue;

  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);

  std::queue<int> std_move(std::move(std_queue));

  EXPECT_EQ(s21_move.front(), std_move.front());
  EXPECT_EQ(s21_move.back(), std_move.back());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(Queue, Copy_Operator) {
  s21::queue<int> s21_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  s21::queue<double> s21_queue_double = {3.5, 6.2, 9.4};
  std::queue<double> std_queue_double;

  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);

  std_queue_double.push(3.5);
  std_queue_double.push(6.2);
  std_queue_double.push(9.4);

  s21::queue<int> s21_queue_empty_int;
  std::queue<int> std_queue_empty_int;
  s21::queue<double> s21_queue_empty_double;
  std::queue<double> std_queue_empty_double;

  s21_queue_empty_int = s21_queue_int;
  std_queue_empty_int = std_queue_int;
  s21_queue_empty_double = s21_queue_double;
  std_queue_empty_double = std_queue_double;

  EXPECT_EQ(s21_queue_empty_int.back(), std_queue_empty_int.back());
  EXPECT_EQ(s21_queue_int.empty(), std_queue_int.empty());
  EXPECT_EQ(s21_queue_empty_double.back(), std_queue_empty_double.back());
  EXPECT_EQ(s21_queue_double.empty(), std_queue_double.empty());
}

TEST(Queue, Move_Operator) {
  s21::queue<int> s21_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  s21::queue<double> s21_queue_double = {3.5, 6.2, 9.4};
  std::queue<double> std_queue_double;

  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);

  std_queue_double.push(3.5);
  std_queue_double.push(6.2);
  std_queue_double.push(9.4);

  s21::queue<int> s21_queue_empty_int;
  std::queue<int> std_queue_empty_int;
  s21::queue<double> s21_queue_empty_double;
  std::queue<double> std_queue_empty_double;

  s21_queue_empty_int = std::move(s21_queue_int);
  std_queue_empty_int = std::move(std_queue_int);
  s21_queue_empty_double = std::move(s21_queue_double);
  std_queue_empty_double = std::move(std_queue_double);

  EXPECT_EQ(s21_queue_empty_int.back(), std_queue_empty_int.back());
  EXPECT_EQ(s21_queue_int.empty(), std_queue_int.empty());
  EXPECT_EQ(s21_queue_empty_double.back(), std_queue_empty_double.back());
  EXPECT_EQ(s21_queue_double.empty(), std_queue_double.empty());
}

TEST(Queue, Size) {
  s21::queue<int> s21_queue_int{1, 4, 8, 9, 1};
  s21::queue<double> s21_queue_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::queue<std::string> s21_queue_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_queue_int.size(), 5U);
  EXPECT_EQ(s21_queue_int.back(), 1);

  EXPECT_EQ(s21_queue_double.size(), 5U);
  EXPECT_EQ(s21_queue_double.back(), 1.1);

  EXPECT_EQ(s21_queue_string.size(), 5U);
  EXPECT_EQ(s21_queue_string.back(), "!!");
}

TEST(Queue, Push) {
  s21::queue<int> s21_queue_int;

  s21_queue_int.push(1);
  s21_queue_int.push(2);
  s21_queue_int.push(3);

  std::queue<int> std_queue_int;

  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);

  EXPECT_EQ(s21_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(s21_queue_int.back(), std_queue_int.back());
}

TEST(Queue, Pop) {
  s21::queue<int> s21_queue_int;
  s21_queue_int.push(1);
  s21_queue_int.push(2);
  s21_queue_int.push(3);
  s21_queue_int.pop();
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  std_queue_int.pop();
  EXPECT_EQ(s21_queue_int.back(), std_queue_int.back());
  s21_queue_int.pop();
  s21_queue_int.pop();
  std_queue_int.pop();
  std_queue_int.pop();
  EXPECT_EQ(s21_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Swap1) {
  s21::queue<int> s21_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;

  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);

  s21::queue<int> s21_queue_empty;
  std::queue<int> std_queue_empty;

  s21_queue_empty.swap(s21_queue_int);
  std_queue_empty.swap(std_queue_int);

  EXPECT_EQ(s21_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(s21_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Swap2) {
  s21::queue<int> s21_queue_ref_int{1, 4, 2, 9, 1};
  s21::queue<int> s21_queue_res_int;

  s21::queue<double> s21_queue_ref_double{5.4, 4.8, 10.43, 9.1, 1.1};
  s21::queue<double> s21_queue_res_double;

  s21::queue<std::string> s21_queue_ref_string{"Hello", ",", "world", "!!"};
  s21::queue<std::string> s21_queue_res_string;

  s21_queue_ref_int.swap(s21_queue_res_int);
  s21_queue_ref_double.swap(s21_queue_res_double);
  s21_queue_ref_string.swap(s21_queue_res_string);

  EXPECT_EQ(s21_queue_ref_int.size(), 0U);
  EXPECT_EQ(s21_queue_res_int.size(), 5U);
  EXPECT_EQ(s21_queue_res_int.front(), 1);
  EXPECT_EQ(s21_queue_res_int.back(), 1);

  EXPECT_EQ(s21_queue_ref_double.size(), 0U);
  EXPECT_EQ(s21_queue_res_double.size(), 5U);
  EXPECT_EQ(s21_queue_res_double.front(), 5.4);
  EXPECT_EQ(s21_queue_res_double.back(), 1.1);

  EXPECT_EQ(s21_queue_ref_string.size(), 0U);
  EXPECT_EQ(s21_queue_res_string.size(), 4U);
  EXPECT_EQ(s21_queue_res_string.front(), "Hello");
  EXPECT_EQ(s21_queue_res_string.back(), "!!");
}

TEST(Queue, Swap3) {
  s21::queue<int> s21_queue_ref_int{1, 4, 8, 9, 1};
  s21::queue<int> s21_queue_res_int{12, 13, 14};

  s21::queue<double> s21_queue_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::queue<double> s21_queue_res_double{13.0};

  s21::queue<std::string> s21_queue_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::queue<std::string> s21_queue_res_string{"14", "15"};

  s21_queue_ref_int.swap(s21_queue_res_int);
  s21_queue_ref_double.swap(s21_queue_res_double);
  s21_queue_ref_string.swap(s21_queue_res_string);

  EXPECT_EQ(s21_queue_ref_int.size(), 3U);
  EXPECT_EQ(s21_queue_ref_int.back(), 14);
  EXPECT_EQ(s21_queue_res_int.size(), 5U);
  EXPECT_EQ(s21_queue_res_int.back(), 1);

  EXPECT_EQ(s21_queue_ref_double.size(), 1U);
  EXPECT_EQ(s21_queue_ref_double.back(), 13.0);
  EXPECT_EQ(s21_queue_res_double.size(), 5U);
  EXPECT_EQ(s21_queue_res_double.back(), 1.1);

  EXPECT_EQ(s21_queue_ref_string.size(), 2U);
  EXPECT_EQ(s21_queue_ref_string.back(), "15");
  EXPECT_EQ(s21_queue_res_string.size(), 5U);
  EXPECT_EQ(s21_queue_res_string.back(), "!!");
}

TEST(Queue, Insert_Many_Back1) {
  s21::queue<int> s21_queue_int;

  s21_queue_int.insert_many_back(1, 2, 3);

  EXPECT_EQ(s21_queue_int.back(), 3);
}

TEST(Queue, Insert_Many_Back2) {
  s21::queue<int> s21_queue_int{7};

  s21_queue_int.insert_many_back(1, 2, 3);

  EXPECT_EQ(s21_queue_int.front(), 7);
  EXPECT_EQ(s21_queue_int.back(), 3);
  s21_queue_int.pop();
  EXPECT_EQ(s21_queue_int.front(), 1);
  s21_queue_int.pop();
  EXPECT_EQ(s21_queue_int.front(), 2);
}

TEST(Queue, Insert_Many_Back3) {
  s21::queue<std::string> s21_queue_int{"Hello"};

  s21_queue_int.insert_many_back("World", "!");

  EXPECT_EQ(s21_queue_int.front(), "Hello");
  s21_queue_int.pop();
  EXPECT_EQ(s21_queue_int.front(), "World");
  s21_queue_int.pop();
  EXPECT_EQ(s21_queue_int.front(), "!");
}