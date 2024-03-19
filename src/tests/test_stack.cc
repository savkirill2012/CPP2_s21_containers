#include <stack>

#include "main.h"

TEST(Stack, Constructor_Default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Constructor_List) {
  s21::stack<int> s21_stack = {1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);

  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Constructor_Copy) {
  s21::stack<int> s21_stack = {1, 2, 3};
  s21::stack<int> s21_copy(s21_stack);
  std::stack<int> std_stack;

  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);

  std::stack<int> std_copy(std_stack);

  EXPECT_EQ(s21_copy.top(), std_copy.top());
}

TEST(Stack, Operator_Copy) {
  s21::stack<int> s21_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;

  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);

  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;

  s21_stack_empty = s21_stack_int;
  std_stack_empty = std_stack_int;

  EXPECT_EQ(s21_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(s21_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Constructor_Move) {
  s21::stack<int> s21_stack = {1, 2, 3};
  s21::stack<int> s21_move(std::move(s21_stack));
  std::stack<int> std_stack;

  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);

  std::stack<int> std_move(std::move(std_stack));

  EXPECT_EQ(s21_move.top(), std_move.top());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Operator_Move) {
  s21::stack<int> s21_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;

  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);

  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;

  s21_stack_empty = std::move(s21_stack_int);
  std_stack_empty = std::move(std_stack_int);

  EXPECT_EQ(s21_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(s21_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Top) {
  s21::stack<int> s21_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;

  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);

  s21::stack<double> s21_stack_double = {1.1f, 2.1f, 3.1f};
  std::stack<double> std_stack_double;

  std_stack_double.push(1.1f);
  std_stack_double.push(2.1f);
  std_stack_double.push(3.1f);

  s21::stack<std::string> s21_stack_string = {"abc", "def", "ghf"};
  std::stack<std::string> std_stack_string;

  std_stack_string.push("abc");
  std_stack_string.push("def");
  std_stack_string.push("ghf");

  EXPECT_EQ(s21_stack_int.top(), std_stack_int.top());
  EXPECT_EQ(s21_stack_double.top(), std_stack_double.top());
  EXPECT_EQ(s21_stack_string.top(), std_stack_string.top());
}

TEST(Stack, Empty) {
  s21::stack<int> s21_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;

  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);

  EXPECT_EQ(s21_stack_int.empty(), std_stack_int.empty());

  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;

  EXPECT_EQ(s21_stack_empty.empty(), std_stack_empty.empty());
}

TEST(Stack, Size1) {
  s21::stack<int> s21_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;

  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);

  EXPECT_EQ(s21_stack_int.size(), std_stack_int.size());

  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;

  EXPECT_EQ(s21_stack_empty.size(), std_stack_empty.size());
}

TEST(Stack, Size2) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_stack_int.size(), 5U);
  EXPECT_EQ(s21_stack_int.top(), 1);

  EXPECT_EQ(s21_stack_double.size(), 5U);
  EXPECT_EQ(s21_stack_double.top(), 1.1);

  EXPECT_EQ(s21_stack_string.size(), 5U);
  EXPECT_EQ(s21_stack_string.top(), "!!");
}

TEST(Stack, Push) {
  s21::stack<int> s21_stack_int;

  s21_stack_int.push(1);
  s21_stack_int.push(2);
  s21_stack_int.push(3);

  std::stack<int> std_stack_int;

  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);

  EXPECT_EQ(s21_stack_int.top(), std_stack_int.top());
}

TEST(Stack, Pop) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.push(1);
  s21_stack_int.push(2);
  s21_stack_int.push(3);
  s21_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  EXPECT_EQ(s21_stack_int.top(), std_stack_int.top());
  s21_stack_int.pop();
  s21_stack_int.pop();
  std_stack_int.pop();
  std_stack_int.pop();
  EXPECT_EQ(s21_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Swap1) {
  s21::stack<int> s21_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;

  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);

  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;

  s21_stack_empty.swap(s21_stack_int);
  std_stack_empty.swap(std_stack_int);

  EXPECT_EQ(s21_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(s21_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Swap2) {
  s21::stack<int> s21_stack_ref_int{1, 4, 2, 9, 1};
  s21::stack<int> s21_stack_res_int;

  s21::stack<double> s21_stack_ref_double{5.4, 4.8, 10.43, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double;

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!!"};
  s21::stack<std::string> s21_stack_res_string;

  s21_stack_ref_int.swap(s21_stack_res_int);
  s21_stack_ref_double.swap(s21_stack_res_double);
  s21_stack_ref_string.swap(s21_stack_res_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 0U);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 0U);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 0U);
  EXPECT_EQ(s21_stack_res_string.size(), 4U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(Stack, Swap3) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int{12, 13, 14};

  s21::stack<double> s21_stack_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double{13.0};

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string{"14", "15"};

  s21_stack_ref_int.swap(s21_stack_res_int);
  s21_stack_ref_double.swap(s21_stack_res_double);
  s21_stack_ref_string.swap(s21_stack_res_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 3U);
  EXPECT_EQ(s21_stack_ref_int.top(), 14);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 1U);
  EXPECT_EQ(s21_stack_ref_double.top(), 13.0);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 2U);
  EXPECT_EQ(s21_stack_ref_string.top(), "15");
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(Stack, Insert_Many_Front1) {
  s21::stack<int> s21_stack_int;

  s21_stack_int.insert_many_front(1, 2, 3);

  EXPECT_EQ(s21_stack_int.top(), 1);
}

TEST(Stack, Insert_Many_Front2) {
  s21::stack<int> s21_stack_int{7};

  s21_stack_int.insert_many_front(1, 2, 3);

  EXPECT_EQ(s21_stack_int.top(), 7);
  s21_stack_int.pop();
  EXPECT_EQ(s21_stack_int.top(), 1);
  s21_stack_int.pop();
  EXPECT_EQ(s21_stack_int.top(), 2);
  s21_stack_int.pop();
  EXPECT_EQ(s21_stack_int.top(), 3);
}

TEST(Stack, Insert_Many_Front3) {
  s21::stack<std::string> s21_stack_str{"Hello"};

  s21_stack_str.insert_many_front("World", "!");

  EXPECT_EQ(s21_stack_str.top(), "Hello");
  s21_stack_str.pop();
  EXPECT_EQ(s21_stack_str.top(), "World");
  s21_stack_str.pop();
  EXPECT_EQ(s21_stack_str.top(), "!");
}