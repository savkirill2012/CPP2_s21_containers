#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_

#include <initializer_list>

#include "../../s21_containers.h"

namespace s21 {

template <class T, class C = list<T> >
class queue {
 private:
  C arr_;

 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q) noexcept;
  queue &operator=(const queue &q);
  queue &operator=(queue &&q) noexcept;
  ~queue();

  const_reference front();
  const_reference back();

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(queue &other) noexcept;

  template <class... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

#include "s21_queue.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_
