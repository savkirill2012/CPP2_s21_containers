namespace s21 {

template <typename T, std::size_t N>
array<T, N>::array() : size_(N) {
  data_ = new value_type[size_]{};
}

template <typename T, std::size_t N>
array<T, N>::~array() {
  if (data_) {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const std::initializer_list<value_type> &items) noexcept
    : array() {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N> &a) noexcept : array() {
  std::copy(a.data_, a.data_ + N, data_);
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N> &&a) noexcept : array() {
  std::move(a.data_, a.data_ + N, data_);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() const noexcept {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  return this->operator[](pos);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  return this->operator[](pos);
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() noexcept {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() noexcept {
  size_type tmpN = N ? N - 1 : N;
  return data_[tmpN];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const noexcept {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const noexcept {
  size_type tmpN = N ? N - 1 : N;
  return data_[tmpN];
}

template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return !size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return size();
}

template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N> &other) noexcept {
  std::swap_ranges(data_, data_ + N, other.data_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) noexcept {
  std::fill(data_, data_ + N, value);
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array<T, N> &a) noexcept {
  if (this != &a) std::copy(a.data_, a.data_ + N, data_);

  return *this;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&a) noexcept {
  if (this != &a) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = std::move(a.data_[i]);
    }
  }

  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of array range");
  }

  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of array range");
  }

  return data_[pos];
}

}  // namespace s21
