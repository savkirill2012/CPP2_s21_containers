namespace s21 {

template <class T, class C>
queue<T, C>::queue() : arr_() {}

template <class T, class C>
queue<T, C>::queue(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push((*i));
  }
}

template <class T, class C>
queue<T, C>::queue(const queue &q) : arr_(q.arr_) {}

template <class T, class C>
queue<T, C>::queue(queue &&q) noexcept : arr_(std::move(q.arr_)) {}

template <class T, class C>
queue<T, C> &queue<T, C>::operator=(const queue &q) {
  if (this != &q) {
    arr_ = q.arr_;
  }
  return *this;
}

template <class T, class C>
queue<T, C> &queue<T, C>::operator=(queue &&q) noexcept {
  arr_ = std::move(q.arr_);
  return *this;
}

template <class T, class C>
queue<T, C>::~queue() {}

template <class T, class C>
typename queue<T, C>::const_reference queue<T, C>::front() {
  return arr_.front();
}

template <class T, class C>
typename queue<T, C>::const_reference queue<T, C>::back() {
  return arr_.back();
}

template <class T, class C>
bool queue<T, C>::empty() const {
  return arr_.empty();
}

template <class T, class C>
typename queue<T, C>::size_type queue<T, C>::size() const {
  return arr_.size();
}

template <class T, class C>
void queue<T, C>::push(const_reference value) {
  arr_.push_back(value);
}

template <class T, class C>
void queue<T, C>::pop() {
  arr_.pop_front();
}

template <class T, class C>
void queue<T, C>::swap(queue &other) noexcept {
  arr_.swap(other.arr_);
}

template <class T, class C>
template <class... Args>
void queue<T, C>::insert_many_back(Args &&...args) {
  arr_.insert_many_back(args...);
}

}  // namespace s21
