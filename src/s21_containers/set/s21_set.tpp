namespace s21 {
template <typename T>
set<T>::set() : tree_(RBTree<T, T>()) {}
template <typename T>
set<T>::set(std::initializer_list<value_type> const &items) {
  for (size_type i = 0; i < items.size(); ++i) {
    value_type val = *(items.begin() + i);
    tree_.add(val, val);
  }
}
template <typename T>
set<T>::set(const set &s) {
  tree_ = s.tree_;
}
template <typename T>
set<T>::set(set &&s) {
  if (this != &s) {
    tree_ = std::move(s.tree_);
  }
}
template <typename T>
set<T>::~set() {}
template <typename T>
set<T> set<T>::operator=(set &&s) {
  if (this == &s) {
    return *this;
  }
  tree_ = std::move(tree_);
  return *this;
}
template <typename T>
typename set<T>::iterator set<T>::begin() {
  return tree_.begin_m();
}
template <typename T>
typename set<T>::iterator set<T>::begin() const  // сделать
{
  return tree_.begin_m();
}

template <typename T>
typename set<T>::iterator set<T>::end()  // сделать
{
  return tree_.end_m();
}

template <typename T>
typename set<T>::iterator set<T>::end() const  // сделать
{
  return tree_.end_m();
}
template <typename T>
bool set<T>::empty() {
  return tree_.empty();
}
template <typename T>
bool set<T>::empty() const {
  return tree_.empty();
}
template <typename T>
typename set<T>::size_type set<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(RBNode<T, T>);
}
template <typename T>
typename set<T>::size_type set<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(RBNode<T, T>);
}
template <typename T>
typename set<T>::size_type set<T>::size() {
  return tree_.GetSizeM();
}
template <typename T>
typename set<T>::size_type set<T>::size() const {
  return tree_.GetSizeM();
}
template <typename T>
void set<T>::clear() {
  tree_.clear();
}
template <typename T>
bool set<T>::contains(const T &key) {
  for (iterator i = this->begin(); i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return true;
    }
  }
  return false;
}

template <typename T>
bool set<T>::contains(const T &key) const {
  for (iterator i = this->begin(); i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return true;
    }
  }
  return false;
}
template <typename T>
typename set<T>::iterator set<T>::find(const T &key) {
  for (iterator i = this->begin(); i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return i;
    }
  }
  return end();
}
template <typename T>
typename set<T>::const_iterator set<T>::find(const T &key) const {
  for (const_iterator i = this->begin(); i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return i;
    }
  }
  return end();
}
template <typename T>
void set<T>::merge(set &other) {
  for (iterator start = other.tree_.begin(), end = other.tree_.end();
       start != end;) {
    tree_.add(start.GetPointer()->GetKey(), start.GetPointer()->GetValue());
    ++start;
  }
  other.clear();
}
template <typename T>
void set<T>::swap(set &other) {
  RBTree<T, T> tmp = tree_;
  tree_ = other.tree_;
  other.tree_ = tmp;
}
template <typename T>
void set<T>::erase(iterator pos) {
  this->tree_.remove(pos.GetPointer()->GetKey());
}
template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type &value) {
  RBNode<T, T> *NodePointer = tree_.GetNode(value);
  if (!NodePointer) {
    return std::make_pair(iterator(NodePointer), false);
  } else {
    tree_.add(value, value);
    RBNode<T, T> *node = tree_.GetNode(value);
    if (node) {
      return std::make_pair(iterator(node), true);
    } else {
      return std::make_pair(iterator(node), false);
    }
  }
}
template <typename T>
template <class... Args>
std::vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    Args &&...args) {
  std::vector<std::pair<typename set<T>::iterator, bool>> ret;
  for (const auto &arg : {args...}) {
    ret.push_back(insert(arg));
  }
  return ret;
}

}  // namespace s21
