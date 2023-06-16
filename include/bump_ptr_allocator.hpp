// Bump Pointer Allocator
// Useful for ensuring large allocated objects are contiguous in memory.

#ifndef _SKTL_CONTAINERS_BUMP_PTR_ALLOCATOR_HPP_
#define _SKTL_CONTAINERS_BUMP_PTR_ALLOCATOR_HPP_

#include <cstdint>
#include <cstdlib>

#include "static_vector.hpp"

namespace SKTL {
namespace Containers {

class BumpPtrAllocator {
 public:
  char *Allocate(int size) {
    if (size >= (end_ - current_)) {
      current_ = (char *)malloc(kSlabSize_);
      end_ = current_ + kSlabSize_;
      slabs_.push_back(current_);
    }
    char *ptr = current_;
    current_ += size;
    return ptr;
  }

 private:
  static constexpr int64_t kSlabSize_ = 4096;
  StaticVector<char *, 4> slabs_;
  char *current_;
  char *end_;
};

};  // namespace Containers
};  // namespace SKTL

#endif  // _SKTL_CONTAINERS_BUMP_PTR_ALLOCATOR_HPP_
