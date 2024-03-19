namespace s21 {

template <class T, class C>
stack<T, C>::stack() : arr_() {}

template <class T, class C>
stack<T, C>::stack(std::initializer_list<value_type> const& items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push((*i));
  }
}

template <class T, class C>
stack<T, C>::stack(const stack& s) : arr_(s.arr_) {}

template <class T, class C>
stack<T, C>::stack(stack&& s) noexcept : arr_(std::move(s.arr_)) {}

template <class T, class C>
stack<T, C>& stack<T, C>::operator=(const stack& s) {
  if (this != &s) {
    arr_ = s.arr_;
  }
  return *this;
}

template <class T, class C>
stack<T, C>& stack<T, C>::operator=(stack&& s) noexcept {
  arr_ = std::move(s.arr_);
  return *this;
}

template <class T, class C>
stack<T, C>::~stack() {}

template <class T, class C>
typename stack<T, C>::const_reference stack<T, C>::top() const {
  return arr_.back();
}

template <class T, class C>
bool stack<T, C>::empty() const {
  return arr_.empty();
}

template <class T, class C>
typename stack<T, C>::size_type stack<T, C>::size() const {
  return arr_.size();
}

template <class T, class C>
void stack<T, C>::push(const_reference value) {
  arr_.push_back(value);
}

template <class T, class C>
void stack<T, C>::pop() {
  arr_.pop_back();
}

template <class T, class C>
void stack<T, C>::swap(stack& other) noexcept {
  arr_.swap(other.arr_);
}

template <class T, class C>
template <class... Args>
void stack<T, C>::insert_many_front(Args&&... args) {
  arr_.insert_many_front(args...);
}

}  // namespace s21
