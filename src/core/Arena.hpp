#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

namespace core::memory {
class Arena {
  static constexpr size_t DEFAULT_BLOCK_SIZE = 64 * 1024;

  struct Block {
    std::unique_ptr<char[]> data;
    size_t offset;
    size_t size;

    explicit Block(size_t sz)
        : data(std::make_unique<char[]>(sz)), offset(0), size(sz) {}
  };

  std::vector<Block> blocks;

public:
  Arena() { blocks.emplace_back(DEFAULT_BLOCK_SIZE); }

  void *allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
    Block *b = &blocks.back();

    void *ptr = b->data.get() + b->offset;
    size_t space = b->size - b->offset;

    if (void *aligned = std::align(alignment, size, ptr, space)) {
      b->offset = b->size - space + size;
      return aligned;
    }

    size_t blockSize = std::max(size + alignment, DEFAULT_BLOCK_SIZE);
    blocks.emplace_back(blockSize);
    return allocate(size, alignment);
  }

  template <typename T, typename... Args> T *create(Args &&...args) {
    void *mem = allocate(sizeof(T), alignof(T));
    return new (mem) T(std::forward<Args>(args)...);
  }

  void reset() {
    blocks.clear();
    blocks.emplace_back(DEFAULT_BLOCK_SIZE);
  }
};

} // namespace core::memory