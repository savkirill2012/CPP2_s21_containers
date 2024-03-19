namespace s21 {

template <typename T>
list<T>::list() {
  size_ = 0;
  head_ = nullptr;
  end_ = nullptr;
}

template <typename T>
list<T>::list(size_type n) : list() {
  if (n > 0)
    for (size_type i = 0; i < n; ++i) push_front(value_type());
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) noexcept
    : list() {
  for (auto i = items.begin(); i != items.end(); i++) push_back(*i);
}

template <typename T>
list<T>::list(const list &l) noexcept : list() {
  Node *current = l.head_;
  while (current) {
    push_back(current->value_);
    current = current->next_;
  }
}

template <typename T>
list<T>::list(list &&l) noexcept {
  head_ = l.head_;
  end_ = l.end_;
  size_ = l.size_;
  l.head_ = nullptr;
  l.end_ = nullptr;
  l.size_ = 0;
}

template <typename T>
list<T>::~list() {
  while (end_) pop_back();
}

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(const list &l) noexcept {
  if (this != &l) {
    list tmp(l);
    clear();
    swap(tmp);
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const noexcept {
  return this->head_->value_;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const noexcept {
  return this->end_->value_;
}

template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return iterator(this->head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return iterator(this->end_);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const noexcept {
  return const_iterator(this->head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const noexcept {
  return const_iterator(this->end_);
}

template <typename T>
bool list<T>::empty() const noexcept {
  return this->size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return this->size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
#ifdef __linux__
  return (std::numeric_limits<size_type>::max() / sizeof(Node)) / 2;
#else
  return std::numeric_limits<size_type>::max() / sizeof(Node);
#endif
}

template <typename T>
void list<T>::clear() noexcept {
  while (!empty()) pop_front();
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) noexcept {
  Node *val = new Node(value);
  if (pos.node_ == nullptr) {
    // Позиция указывает на конец списка, вставляем в конец
    if (end_ != nullptr) {
      end_->next_ = val;
      val->prev_ = end_;
      end_ = val;
    } else {
      // Список пуст, новый элемент становится и началом и концом
      head_ = end_ = val;
    }
  } else {
    if (pos.node_->prev_ != nullptr) {
      pos.node_->prev_->next_ = val;
      val->prev_ = pos.node_->prev_;
    } else {
      // Вставляем в начало списка
      head_ = val;
    }
    // Присоединяем новый элемент к текущему
    pos.node_->prev_ = val;
    val->next_ = pos.node_;
  }
  ++size_;
  return iterator(val);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos.node_ == nullptr) {
    throw std::invalid_argument("Invalid iterator");
  }
  Node *current = pos.node_;
  if (current == head_) {
    head_ = current->next_;
  } else {
    current->prev_->next_ = current->next_;
  }

  if (current == end_) {
    end_ = current->prev_;
  } else {
    current->next_->prev_ = current->prev_;
  }

  delete current;
  --size_;
}

template <typename T>
void list<T>::push_back(const_reference value) noexcept {
  Node *node = new Node(value);
  if (empty()) {
    head_ = end_ = node;
  } else {
    end_->next_ = node;
    node->prev_ = end_;
    end_ = node;
  }
  node = nullptr;
  size_++;
}

template <typename T>
void list<T>::pop_back() {
  if (end_ == nullptr) {
    throw std::out_of_range("list is empty!");
  }
  if (end_ == head_) {
    delete head_;
    head_ = end_ = nullptr;
    size_--;
    return;
  }
  Node *node = end_->prev_;
  node->next_ = nullptr;
  delete end_;
  end_ = node;
  size_--;
}

template <typename T>
void list<T>::push_front(const_reference value) noexcept {
  Node *node = new Node(value);
  if (empty()) {
    head_ = end_ = node;
  } else {
    head_->prev_ = node;
    node->next_ = head_;
    head_ = node;
  }
  size_++;
}

template <typename T>
void list<T>::pop_front() {
  if (head_ == nullptr) {
    throw std::out_of_range("list is empty!");
  }
  if (end_ == head_) {
    delete head_;
    head_ = end_ = nullptr;
    size_--;
    return;
  }
  Node *node = head_;
  head_ = head_->next_;
  head_->prev_ = nullptr;
  delete node;
  size_--;
}

template <typename T>
void list<T>::swap(list &other) noexcept {
  if (this != &other) {
    std::swap(head_, other.head_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }
}

template <typename T>
void list<T>::merge(list &other) noexcept {
  if (this == &other || other.empty()) {
    return;
  }

  if (empty()) {
    // Если список this пустой, просто присваиваем head_ и end_ из other.
    head_ = other.head_;
    end_ = other.end_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.end_ = nullptr;
    other.size_ = 0;
    return;
  }

  Node *it1 = head_;
  Node *it2 = other.head_;

  while (it1 != nullptr && it2 != nullptr) {
    if (it2->value_ < it1->value_) {
      Node *next = it2->next_;
      // Вставка элемента из other перед it1
      if (it1->prev_ != nullptr) {
        it1->prev_->next_ = it2;
        it2->prev_ = it1->prev_;
      } else {
        head_ = it2;
        head_->prev_ = nullptr;
      }
      it2->next_ = it1;
      it1->prev_ = it2;
      it2 = next;
    } else {
      it1 = it1->next_;
    }
  }
  // Добавляем оставшиеся элементы из списка other, если есть
  if (it2 != nullptr) {
    // Обновляем связи последнего элемента списка this
    end_->next_ = it2;
    it2->prev_ = end_;
    // Обновляем указатель end_ на последний элемент списка other
    end_ = other.end_;
  }
  // Отсоединяем оставшуюся часть списка other
  other.head_ = nullptr;
  other.end_ = nullptr;
  other.size_ = 0;
  // Увеличиваем размер списка this на размер списка other
  size_ += other.size_;
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) noexcept {
  if (!other.empty() && this != &other) {
    if (pos.node_ == nullptr) {
      // Если позиция указывает на конец списка, вставляем в конец
      if (end_ != nullptr) {
        end_->next_ = other.head_;
        other.head_->prev_ = end_;
        end_ = other.end_;
      } else {
        // Список, в который происходит перемещение, пуст,
        // элементы из other становятся и началом и концом списка
        head_ = other.head_;
        end_ = other.end_;
      }
    } else {
      if (pos.node_->prev_ != nullptr) {
        pos.node_->prev_->next_ = other.head_;
        other.head_->prev_ = pos.node_->prev_;
      } else {
        // Вставляем в начало списка
        head_ = other.head_;
      }
      pos.node_->prev_ = other.end_;
      other.end_->next_ = pos.node_;
    }
    // Обновление размера списков
    size_ += other.size_;
    other.size_ = 0;
    // Очистка другого списка
    other.head_ = nullptr;
    other.end_ = nullptr;
  }
}

template <typename T>
void list<T>::reverse() noexcept {
  if (this->size_ > 1) {
    Node *node = this->head_;
    for (size_type i = 0; i < this->size_; ++i) {
      std::swap(node->prev_, node->next_);
      node = node->prev_;
    }
    std::swap(this->head_, this->end_);
  }
}

template <typename T>
void list<T>::unique() noexcept {
  if (!this->empty()) {
    for (iterator i = begin(); i != end();) {
      iterator it = i;
      it++;
      if (it.node_ == nullptr) {
        return;
      } else if (*i == *it) {
        erase(it);
      } else {
        i++;
      }
    }
  }
}

template <typename T>
void list<T>::sort() noexcept {
  if (head_ != nullptr) {
    Node *last = end_;
    quickSort(head_, last);
  }
}

template <typename T>
typename list<T>::Node *list<T>::partition(Node *low, Node *high) noexcept {
  T pivot = high->value_;
  Node *i = low->prev_;

  for (Node *j = low; j != high; j = j->next_) {
    if (j->value_ < pivot) {
      i = (i == nullptr) ? low : i->next_;
      std::swap(i->value_, j->value_);
    }
  }
  i = (i == nullptr) ? low : i->next_;
  std::swap(i->value_, high->value_);

  return i;
}

template <typename T>
void list<T>::quickSort(Node *low, Node *high) noexcept {
  if (high != nullptr && low != high && low != high->next_) {
    Node *pivot = partition(low, high);
    quickSort(low, pivot->prev_);
    quickSort(pivot->next_, high);
  }
}

template <typename T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) noexcept {
  for (auto &val : {args...}) {
    insert(pos, val);
  }
  return pos;
}

template <typename T>
template <class... Args>
void list<T>::insert_many_back(Args &&...args) noexcept {
  for (auto &val : {args...}) {
    push_back(val);
  }
}

template <typename T>
template <class... Args>
void list<T>::insert_many_front(Args &&...args) noexcept {
  for (auto &val : {args...}) {
    push_front(val);
  }
}

}  // namespace s21
