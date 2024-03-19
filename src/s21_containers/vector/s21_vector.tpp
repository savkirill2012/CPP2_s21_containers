// #include "vector.h"

namespace s21 {

template <typename value_type>
vector<value_type>::vector() : size_(0), buffer_size_(0), massiv_{nullptr} {}

template <typename value_type>
vector<value_type>::vector(size_type n)
    : size_(n), buffer_size_(n), massiv_{new value_type[buffer_size_]{}} {}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const& item)
    : size_(item.size()),
      buffer_size_(size_),
      massiv_{new value_type[buffer_size_]{}} {
  for (size_type i = 0; i < size_; ++i) {
    massiv_[i] = *(item.begin() + i);
  }
}

template <typename value_type>
vector<value_type>::vector(const vector& other)
    : size_(other.size_),
      buffer_size_(other.buffer_size_),
      massiv_{new value_type[buffer_size_]{}} {
  for (size_type i = 0; i < buffer_size_; ++i) {
    massiv_[i] = other.massiv_[i];
  }
}

template <typename value_type>
vector<value_type>::vector(vector&& other)
    : size_(other.size_),
      buffer_size_(other.buffer_size_),
      massiv_(other.massiv_) {
  other.massiv_ = nullptr;
}

template <typename value_type>
vector<value_type>::~vector() {
  delete[] massiv_;
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(vector&& other) {
  if (this == &other) return *this;

  std::swap(massiv_, other.massiv_);  // check may not work
  size_ = other.size_;
  buffer_size_ = other.buffer_size_;
  return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(
    size_type pos) const {
  if (pos >= buffer_size_) {
    throw std::out_of_range("Out of range");
  } else {
    return massiv_[pos];
  }
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) const {
  return massiv_[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return massiv_[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  return massiv_[size_ - 1];
}

template <typename T>
T* vector<T>::data() {
  return massiv_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() const {
  return massiv_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() const {
  return massiv_ + size_ - 1;
}

template <typename value_type>
bool vector<value_type>::empty() const {
  if (size_ == 0) {
    return 1;
  } else {
    return 0;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
#ifdef __linux__
  return std::numeric_limits<size_type>::max() / (sizeof(value_type) * 2);
#elif __APPLE__
  return std::numeric_limits<size_type>::max() / (sizeof(value_type));
#else
  return std::numeric_limits<size_type>::max() / (sizeof(value_type));
#endif
}

template <typename value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > buffer_size_) {
    vector tmp(size);
    std::swap(massiv_, tmp.massiv_);
    for (size_t i = 0; i < buffer_size_; ++i) {
      massiv_[i] = tmp.massiv_[i];
    }
    buffer_size_ = size;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return buffer_size_;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (buffer_size_ > size_) {
    vector tmp(size_);
    std::swap(massiv_, tmp.massiv_);
    for (size_t i = 0; i < size_; ++i) {
      massiv_[i] = tmp.massiv_[i];
    }
    buffer_size_ = size_;
  }
}

template <typename value_type>
void vector<value_type>::clear() {
  size_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type num_pos = pos - begin();

  _add_mem_if_need();

  for (size_type i = size_; i > num_pos; --i) {
    massiv_[i] = massiv_[i - 1];
  }

  massiv_[num_pos] = value;
  size_++;

  return massiv_ + num_pos;
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  size_type num_pos = pos - begin();

  for (size_type i = num_pos; i < size_ - 1; ++i) {
    massiv_[i] = massiv_[i + 1];
  }

  size_--;
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  _add_mem_if_need();

  massiv_[size_] = value;
  size_++;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  size_--;
}

template <typename value_type>
void vector<value_type>::swap(vector& other) {
  std::swap(size_, other.size_);
  std::swap(buffer_size_, other.buffer_size_);
  std::swap(massiv_, other.massiv_);
}

template <typename value_type>
void vector<value_type>::_add_mem_if_need() {
  if (size_ + 1 > buffer_size_) {
    size_type pos = 1;
    while (pos < size_ + 1) {
      pos *= 2;
    }

    value_type* tmp = new value_type[pos]{};
    for (size_type i = 0; i < buffer_size_; ++i) {
      tmp[i] = massiv_[i];
    }
    delete[] massiv_;
    buffer_size_ = pos;
    massiv_ = tmp;
  }
}
}  // namespace s21
