#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

#include "../heap.hpp"
#include "../../vector/vector.hpp"

#include <cmath>

namespace lasd {
  template <typename Data>
  class HeapVec: virtual public Heap<Data>, virtual protected Vector<Data> {
    protected:
      using Container::size;
      using Vector<Data>::elements;
    public:
      // Default constructor
      HeapVec() = default;

      // Specific constructors
      HeapVec(const TraversableContainer<Data>&); // A heap obtained from a TraversableContainer
      HeapVec(MappableContainer<Data>&&) noexcept; // A heap obtained from a MappableContainer

      // Copy constructor
      HeapVec(const HeapVec&);

      // Move constructor
      HeapVec(HeapVec&&) noexcept;

      // Destructor
      virtual ~HeapVec() = default;

      // Copy assignment
      HeapVec& operator = (const HeapVec&);

      // Move assignment
      HeapVec& operator = (HeapVec&&) noexcept;

      // Comparison operators
      inline bool operator == (const HeapVec&) const noexcept;
      inline bool operator != (const HeapVec&) const noexcept;

      // Specific member functions (inherited from Heap)
      bool IsHeap() const noexcept override; // Override Heap member

      inline void Heapify() noexcept override; // Override Heap member

      // Specific member function (inherited from SortableLinearContainer)
      inline void Sort() noexcept override; // Override SortableLinearContainer member

      // Specific member function (inherited from ClearableContainer (Vector's overridden version))
      using Vector<Data>::Clear;

      // Specific member function (inherited from Vector (both MutableLinearContainer and LinearContainer's versions))
      using Vector<Data>::operator[];
      using Vector<Data>::Front;
      using Vector<Data>::Back;
    protected:
      // Auxiliary functions
      void Heapify(ulong, ulong) noexcept;

      void HeapSort() noexcept;
  };
}

#include "heapvec.cpp"

#endif