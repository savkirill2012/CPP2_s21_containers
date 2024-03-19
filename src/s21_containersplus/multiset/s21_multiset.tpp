namespace s21 {
template <typename K>
multiset<K>::multiset() : tree_(RBTree<K, K>()) {}

template <typename K>
multiset<K>::multiset(std::initializer_list<value_type> const& items) {
  for (size_type i = 0; i < items.size(); ++i) {
    value_type val = *(items.begin() + i);
    tree_.add(val, val);
  }
}

template <typename K>
multiset<K>::multiset(const multiset& ms) {
  tree_ = ms.tree_;
}

template <typename K>
multiset<K>::multiset(multiset&& ms) {
  std::swap(tree_, ms.tree_);
}

template <typename K>
multiset<K>::~multiset() {}

template <typename K>
multiset<K>& multiset<K>::operator=(const multiset& ms) {
  if (this == &ms) return *this;
  tree_ = ms.tree_;
  return *this;
}

template <typename K>
multiset<K>& multiset<K>::operator=(multiset&& ms) {
  if (this == &ms) return *this;
  std::swap(tree_, ms.tree_);
  return *this;
}

template <typename K>
typename multiset<K>::iterator multiset<K>::begin() const {
  return tree_.begin_m();
}

template <typename K>
typename multiset<K>::iterator multiset<K>::end() const {
  return tree_.end_m();
}

template <typename K>
bool multiset<K>::empty() const {
  return tree_.empty();
}

template <typename K>
typename multiset<K>::size_type multiset<K>::size() const {
  return tree_.GetSizeM();
}

template <typename K>
typename multiset<K>::size_type multiset<K>::max_size() const {  // need test
  size_type temp = ((size_type)pow(2, ENVIRONMENT) / (sizeof(value_type) * 2));
  return temp;
}

template <typename K>
void multiset<K>::clear() {
  tree_.clear();
}

template <typename K>
typename multiset<K>::iterator multiset<K>::insert(const value_type& value) {
  tree_.add(value, value);
  RBNode<K, K>* node = tree_.GetNode(value);
  return iterator(node, tree_.SearchPrevNode(node));
}

template <typename K>
void multiset<K>::erase(iterator pos) {
  K key = pos.GetPointer()->GetKey();
  tree_.remove_m(key);
}

template <typename K>
void multiset<K>::swap(multiset& other) {
  RBTree<K, K> tmp = tree_;
  tree_ = other.tree_;
  other.tree_ = tmp;
}

template <typename K>
void multiset<K>::merge(multiset& other) {
  for (iterator start = other.tree_.begin_m(), end = other.tree_.end_m();
       start != end;) {
    tree_.add(start.GetPointer()->GetKey(), start.GetPointer()->GetKey());
    ++start;
  }
  other.clear();
}

template <typename K>
typename multiset<K>::size_type multiset<K>::count(const K& key) const {
  return tree_.GetNode(key)->GetLocCounter();
}

template <typename K>
typename multiset<K>::iterator multiset<K>::find(const K& key) const {
  RBNode<K, K>* node = tree_.GetNode(key);
  return iterator(node, tree_.SearchPrevNode(node));
}

template <typename K>
bool multiset<K>::contains(const K& key) const {
  if (tree_.GetNode(key)->GetColor() == -1) {
    return false;
  } else {
    return true;
  }
}

template <typename K>
std::pair<typename multiset<K>::iterator, typename multiset<K>::iterator>
multiset<K>::equal_range(const K& key) const {
  RBNode<K, K>* node = tree_.GetNode(key);
  iterator curent(node, tree_.SearchPrevNode(node));
  iterator next(curent);
  while (static_cast<_RBTree_iterator_map<K, K>>(next).GetPointer()->GetKey() ==
         node->GetKey()) {
    ++next;
  }

  return std::pair<iterator, iterator>(curent, next);
}

template <typename K>
typename multiset<K>::iterator multiset<K>::lower_bound(const K& key) const {
  RBNode<K, K>* node = tree_.GetNode(key);
  if (node->GetColor() != -1) {
    return iterator(node, tree_.SearchPrevNode(node));
  } else {
    iterator start = this->begin();
    iterator end = this->end();
    while (start != end) {
      if (*start >= key) {
        return start;
      }
      ++start;
    }
    return start;
  }
}

template <typename K>
typename multiset<K>::iterator multiset<K>::upper_bound(const K& key) const {
  iterator start = this->begin();
  iterator end = this->end();
  while (start != end) {
    if (*start <= key) {
      ++start;
    } else {
      return start;
    }
  }

  return end;
}
}  // namespace s21
