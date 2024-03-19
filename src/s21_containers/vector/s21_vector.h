#ifndef S21_vector_H_
#define S21_vector_H_

#include <math.h>

#include <iostream>

#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT 64
#else
#define ENVIRONMENT 32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT 64
#else
#define ENVIRONMENT 32
#endif
#endif

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &item);
  vector(const vector &other);
  vector(vector &&other);
  ~vector();

  vector<value_type> &operator=(vector &&other);

  // access to elements
  reference at(size_type pos) const;
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T *data();

  // iterators
  iterator begin() const;
  iterator end() const;

  // info about
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // change
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

 private:
  size_type size_;
  size_type buffer_size_;
  T *massiv_;

  void _add_mem_if_need();
};
}  // namespace s21

// think about realization iterator + test own class as template;
#include "s21_vector.tpp"

#endif
