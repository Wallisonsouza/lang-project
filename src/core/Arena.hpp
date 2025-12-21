#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>
#include <type_traits>
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

  // Armazena ponteiros para todos os objetos alocados (opcional, útil para
  // percorrer tudo)
  std::vector<void *> allocated_objects;

public:
  Arena() { blocks.emplace_back(DEFAULT_BLOCK_SIZE); }

  void *allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
    Block *b = &blocks.back();
    void *ptr = b->data.get() + b->offset;
    size_t space = b->size - b->offset;

    if (void *aligned = std::align(alignment, size, ptr, space)) {
      b->offset = b->size - space + size;
      allocated_objects.push_back(aligned); // guarda ponteiro
      return aligned;
    }

    size_t blockSize = std::max(size + alignment, DEFAULT_BLOCK_SIZE);
    blocks.emplace_back(blockSize);
    return allocate(size, alignment);
  }

  template <typename T, typename... Args> T *create(Args &&...args) {
    static_assert(!std::is_array_v<T>, "T não pode ser um array");
    void *mem = allocate(sizeof(T), alignof(T));
    T *obj = new (mem) T(std::forward<Args>(args)...);
    return obj;
  }

  // Retorna todos os objetos alocados
  const std::vector<void *> &get_allocated_objects() const {
    return allocated_objects;
  }

  void reset() {
    blocks.clear();
    blocks.emplace_back(DEFAULT_BLOCK_SIZE);
    allocated_objects.clear();
  }
};

} // namespace core::memory
