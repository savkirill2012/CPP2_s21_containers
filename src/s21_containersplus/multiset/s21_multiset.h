#ifndef S21MULTISET_H_
#define S21MULTISET_H_

#include <math.h>

#include <iostream>

#include "../../rb_tree/s21_rb.h"

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
template <typename K>
class multiset {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<K, K>::iterator_multiset;
  using const_iterator = const typename RBTree<K, K>::iterator_multiset;
  using size_type = std::size_t;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();

  multiset<K>& operator=(const multiset& ms);
  multiset<K>& operator=(multiset&& ms);

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const K& key) const;
  iterator find(const K& key) const;
  bool contains(const K& key) const;
  std::pair<iterator, iterator> equal_range(const K& key) const;
  iterator lower_bound(const K& key) const;
  iterator upper_bound(const K& key) const;
  // std::pair<const_iterator, const_iterator> equal_range(const K& key) const;
  // const_iterator lower_bound(const K& key) const;
  // const_iterator upper_bound(const K& key) const;

 private:
  RBTree<K, K> tree_;
};
}  // namespace s21

#include "s21_multiset.tpp"

#endif
