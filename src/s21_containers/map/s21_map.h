#ifndef MAP_H
#define MAP_H
#include <limits.h>

#include "../../rb_tree/s21_rb.h"
namespace s21 {
template <typename T, typename V>
class map {
 public:
  using key_type = T;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<T, V>::iterator_map;
  using const_iterator = const typename RBTree<T, V>::iterator_map;
  using size_type = size_t;
  using Allocator = std::allocator<RBNode<T, V>>;
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map<T, V> operator=(map &&m);
  mapped_type &at(const T &key);
  mapped_type &at(const T &key) const;
  mapped_type &operator[](const T &key);
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
  std::pair<iterator, bool> insert(const T &key, const V &obj);
  std::pair<iterator, bool> insert_or_assign(const T &key, const V &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);
  bool contains(const T &key);
  bool contains(const T &key) const;
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  RBTree<T, V> tree_;
  Allocator allocator;
};
};  // namespace s21

#include "s21_map.tpp"
#endif
