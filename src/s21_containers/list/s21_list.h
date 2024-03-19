#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_LIST_S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type value_;
    Node *next_ = nullptr;
    Node *prev_ = nullptr;

    Node(const value_type &value) : value_(value) {}
  };

  Node *head_;
  Node *end_;
  size_type size_;

 public:
  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items) noexcept;
  list(const list &l) noexcept;
  list(list &&l) noexcept;
  ~list();
  list &operator=(list &&l) noexcept;
  list &operator=(const list &l) noexcept;

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  void push_back(const_reference value) noexcept;
  void pop_back();
  void push_front(const_reference value) noexcept;
  void pop_front();
  void swap(list &other) noexcept;
  void merge(list &other) noexcept;
  void reverse() noexcept;
  void unique() noexcept;
  void sort() noexcept;

  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { node_ = nullptr; }
    ListIterator(Node *node) noexcept : node_(node) {}

    reference operator*() const {
      if (!this->node_) throw std::invalid_argument("node_ is nullptr");
      return node_->value_;
    }

    ListIterator &operator++() noexcept {
      if (node_) node_ = node_->next_;
      return *this;
    }

    ListIterator &operator--() noexcept {
      if (node_) node_ = node_->prev_;
      return *this;
    }

    ListIterator operator++(int) noexcept {
      if (node_) node_ = node_->next_;
      return *this;
    }

    ListIterator operator--(int) noexcept {
      if (node_) node_ = node_->prev_;
      return *this;
    }

    ListIterator operator+(const size_type value) const noexcept {
      iterator tmp(node_);
      for (size_type i = 0; i < value; i++) tmp++;
      return tmp;
    }

    ListIterator operator-(const size_type value) const noexcept {
      iterator tmp(node_);
      for (size_type i = 0; i < value; i++) tmp--;
      return tmp;
    }

    bool operator<(const ListIterator &other) const noexcept {
      return this->node_ < other.node_;
    }

    bool operator>(const ListIterator &other) const noexcept {
      return this->node_ > other.node_;
    }

    bool operator==(const ListIterator &other) const noexcept {
      return this->node_ == other.node_;
    }

    bool operator!=(const ListIterator &other) const noexcept {
      return this->node_ != other.node_;
    }

   private:
    Node *node_ = nullptr;
    friend class list<T>;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator() : ListIterator<T>() {}
    ListConstIterator(const ListIterator<T> &node) : ListIterator<T>(node) {}
    const_reference operator*() const { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  iterator insert(iterator pos, const_reference value) noexcept;
  void erase(iterator pos);
  void splice(const_iterator pos, list &other) noexcept;

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) noexcept;
  template <class... Args>
  void insert_many_back(Args &&...args) noexcept;
  template <class... Args>
  void insert_many_front(Args &&...args) noexcept;

 private:
  void quickSort(Node *low, Node *high) noexcept;
  Node *partition(Node *low, Node *high) noexcept;
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_CONTAINERS_LIST_S21_LIST_H_
