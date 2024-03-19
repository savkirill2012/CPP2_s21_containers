namespace s21 {
template <typename T, typename V>
map<T, V>::map() : tree_(RBTree<T, V>()) {}

template <typename Key, typename V>
map<Key, V>::map(
    std::initializer_list<typename map<Key, V>::value_type> const &items) {
  for (size_type i = 0; i < items.size(); ++i) {
    value_type val = *(items.begin() + i);
    tree_.add(val.first, val.second);
  }
}
template <typename T, typename V>
map<T, V>::map(const map &m) {
  tree_ = m.tree_;
}  // копия дерева
template <typename T, typename V>
map<T, V>::map(map &&m) {
  tree_ = std::move(m.tree);
}  // копия дерева

template <typename T, typename V>
map<T, V>::~map() {}
template <typename T, typename V>
bool map<T, V>::empty() {
  return tree_.empty();
}
template <typename T, typename V>
bool map<T, V>::empty() const {
  return tree_.empty();
}
template <typename T, typename V>
map<T, V> map<T, V>::operator=(map<T, V> &&m) {
  if (this == &m) {
    return *this;
  }
  std::move(tree_, m.tree_);
  return *this;
}

template <typename T, typename V>
typename map<T, V>::size_type map<T, V>::size() {
  return tree_.len_m();
}
template <typename T, typename V>
typename map<T, V>::size_type map<T, V>::size() const {
  return tree_.GetSizeM();
}
template <typename T, typename V>
typename map<T, V>::size_type map<T, V>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(RBNode<T, V>);
}

template <typename T, typename V>
typename map<T, V>::size_type map<T, V>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(RBNode<T, V>);
}

template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert(
    const value_type &value) {
  return insert(value.first, value.second);
}
template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  if (this->empty()) {
    return insert(std::make_pair(key, obj));
  } else {
    iterator i = this->begin();
    for (; i != this->end(); ++i) {
      if (i.GetPointer()->GetKey() == key) {
        i.GetPointer()->GetValue() = obj;
        return std::make_pair(i, false);
      }
    }
    return insert(std::make_pair(key, obj));
  }
}
template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert(
    const key_type &key, const mapped_type &obj) {
  RBNode<T, V> *NodePointer = tree_.GetNode(key);
  if (!NodePointer) {
    return std::make_pair(iterator(NodePointer), false);
  } else {
    tree_.add(key, obj);
    RBNode<T, V> *node = tree_.GetNode(key);
    if (node) {
      return std::make_pair(iterator(node), true);
    } else {
      return std::make_pair(iterator(node), false);
    }
  }
}
template <typename T, typename V>
bool map<T, V>::contains(const T &key) {
  for (iterator i = this->begin(); i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return true;
    }
  }
  return false;
}
template <typename T, typename V>
bool map<T, V>::contains(const T &key) const {
  for (iterator i = this->begin(); i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return true;
    }
  }
  return false;
}
template <typename T, typename V>
void map<T, V>::clear() {
  tree_.clear();
}
template <typename T, typename V>
void map<T, V>::swap(map &other) {
  RBTree<T, V> tmp = tree_;
  tree_ = other.tree_;
  other.tree_ = tmp;
}

template <typename T, typename V>
void map<T, V>::merge(map &other) {
  for (iterator start = other.tree_.begin(), end = other.tree_.end();
       start != end;) {
    tree_.add(start.GetPointer()->GetKey(), start.GetPointer()->GetValue());
    ++start;
  }
  other.clear();
}
template <typename T, typename V>
void map<T, V>::erase(typename map<T, V>::iterator pos) {
  this->tree_.remove(pos.GetPointer()->GetKey());
}
template <typename T, typename V>
typename map<T, V>::mapped_type &map<T, V>::operator[](const T &key) {
  iterator it = begin();
  for (; it != end(); it++) {
    if (it.GetPointer()->GetKey() == key) {
      return it.GetPointer()->GetValue();
    }
  }
  auto ins = insert(key, mapped_type());
  return ins.first.GetPointer()->GetValue();
}
template <typename T, typename V>
typename map<T, V>::mapped_type &map<T, V>::at(const T &key) {
  iterator i = this->begin();
  for (; i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return i.GetPointer()->GetValue();
    }
  }
  throw std::out_of_range("Map does not have this key");
}
template <typename T, typename V>
typename map<T, V>::mapped_type &map<T, V>::at(const T &key) const {
  iterator i = this->begin();
  for (; i != this->end(); i++) {
    if (i.GetPointer()->GetKey() == key) {
      return i.GetPointer()->GetValue();
    }
  }
  throw std::out_of_range("Map does not have this key");
}
template <typename T, typename V>
template <class... Args>
std::vector<std::pair<typename map<T, V>::iterator, bool>>
map<T, V>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<T, V>::iterator, bool>> ret;
  for (const auto &arg : {args...}) {
    ret.push_back(insert(arg));
  }
  return ret;
}

template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::begin() {
  return tree_.begin_m();
}
template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::begin() const {
  return tree_.begin_m();
}

template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::end() {
  return tree_.end_m();
}

template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::end() const {
  return tree_.end_m();
}
}  // namespace s21