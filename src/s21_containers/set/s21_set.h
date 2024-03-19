#ifndef SET_H
#define SET_H
#include <limits.h>

#include "../../rb_tree/s21_rb.h"
namespace s21 {
template <typename T>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<T, T>::iterator_map;
  using const_iterator = const typename RBTree<T, T>::iterator_map;
  using size_type = size_t;
  using Allocator = std::allocator<T>;
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set<T> operator=(set &&s);
  iterator begin();
  iterator begin() const;
  iterator end();
  iterator end() const;
  size_type max_size();
  size_type max_size() const;
  bool empty();
  bool empty() const;
  size_type size();
  size_type size() const;
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);
  bool contains(const T &value_type);
  bool contains(const T &value_type) const;
  iterator find(const T &key);
  const_iterator find(const T &key) const;
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  RBTree<T, T> tree_;
  Allocator allocator;
};
};  // namespace s21
#include "s21_set.tpp"
#endif
