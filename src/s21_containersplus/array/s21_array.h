#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items) noexcept;
  array(const array &a) noexcept;
  array(array &&a) noexcept;
  ~array();
  array &operator=(const array &a) noexcept;
  array &operator=(array &&a) noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front() noexcept;
  reference back() noexcept;
  const_reference front() const noexcept;
  const_reference back() const noexcept;

  iterator data() const noexcept;
  iterator begin() const noexcept;
  iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(array &other) noexcept;
  void fill(const_reference value) noexcept;

 private:
  value_type *data_;
  size_type size_ = N;
};

}  // namespace s21

#include "s21_array.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_H_
