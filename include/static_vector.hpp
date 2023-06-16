// Small Vector

#ifndef _SKTL_CONTAINERS_SMALL_VECTOR_HPP_
#define _SKTL_CONTAINERS_SMALL_VECTOR_HPP_

#include <cstddef>
#include <cstdint>

namespace SKTL {
namespace Containers {

// TODO: iterator type for begin() end()
template <typename T>
class StaticVectorImpl {
 private:
  T *begin_;
  T *end_;
  size_t size_;
  size_t capacity_;

 protected:
  StaticVectorImpl(T *begin, T *end, size_t size, size_t capacity)
      : begin_(begin), end_(end), size_(size), capacity_(capacity) {}
  StaticVectorImpl(T *begin, T *end, size_t capacity)
      : StaticVectorImpl(begin, end, 0, capacity) {}

 public:
  T *begin() const noexcept { return begin_; }
  T *end() const noexcept { return end_; }
  int32_t PushBack(const T &element) noexcept {
    if (size_ < capacity_) {
      *(begin_ + size_) = element;
      size_ += 1;
      return 0;
    }
    return -1;
  }
  int32_t PopBack() noexcept {
    if (size_) {
      size_ -= 1;
      return 0;
    }
    return -1;
  }
  size_t Size() const noexcept { return size_; }
};

template <typename T, int N>
class StaticVector : public StaticVectorImpl<T> {
 public:
  StaticVector() : StaticVectorImpl<T>((T *)buffer_, (T *)buffer_, N) {}
  char *Data() noexcept { return buffer_; }

 private:
  char buffer_[sizeof(T) * N];
};

};  // namespace Containers
};  // namespace SKTL

#endif  // _SKTL_CONTAINERS_SMALL_VECTOR_HPP_
