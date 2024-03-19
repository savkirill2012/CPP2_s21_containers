#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_STACK_S21_STACK_H_

#include <initializer_list>
#include <utility>

#include "../../s21_containers.h"

namespace s21 {

template <class T, class C = list<T> >
class stack {
 private:
  C arr_;

 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();  // Default constructor
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);                 // Copy constructor
  stack(stack &&s) noexcept;             // Move constructor
  stack &operator=(const stack &s);      // Copy assignment operator
  stack &operator=(stack &&s) noexcept;  // Mova assignment operator
  ~stack();

  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(stack &other) noexcept;

  template <class... Args>
  void insert_many_front(Args &&...args);
};

}  // namespace s21

#include "s21_stack.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_STACK_S21_STACK_H_
