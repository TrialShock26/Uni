#ifndef HEAP_HPP
#define HEAP_HPP

#include "../container/linear.hpp"

namespace lasd {
  template <typename Data>
  class Heap: virtual public SortableLinearContainer<Data>, virtual public ClearableContainer {
    public:
      // Default destructor
      virtual ~Heap() = default;

      // Copy assignment
      Heap& operator = (const Heap&) = delete;

      // Move assignment
      Heap& operator = (Heap&&) noexcept = delete;

      // Specific member functions
      virtual bool IsHeap() const noexcept = 0;

      virtual void Heapify() noexcept = 0;
  };
}

#endif