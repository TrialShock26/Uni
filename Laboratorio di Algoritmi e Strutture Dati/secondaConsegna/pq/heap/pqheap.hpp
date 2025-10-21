#ifndef PQHEAP_HPP
#define PQHEAP_HPP

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

namespace lasd {
  template <typename Data>
  class PQHeap: virtual public PQ<Data>, virtual protected HeapVec<Data> {
    protected:
      using Container::size;
      using Vector<Data>::elements;
      ulong capacity = 0;
    public:
      // Default constructor
      PQHeap() = default;
    
      // Specific constructors
      PQHeap(const TraversableContainer<Data>&); // A priority queue obtained from a TraversableContainer
      PQHeap(MappableContainer<Data>&&) noexcept; // A priority queue obtained from a MappableContainer
    
      // Copy constructor
      PQHeap(const PQHeap&);
    
      // Move constructor
      PQHeap(PQHeap&&) noexcept;
    
      // Destructor
      ~PQHeap() = default;
    
      // Copy assignment
      PQHeap& operator = (const PQHeap&);
    
      // Move assignment
      PQHeap& operator = (PQHeap&&) noexcept;

      // Comparison operators
      inline bool operator == (const PQHeap&) const noexcept;
      inline bool operator != (const PQHeap&) const noexcept;
    
      // Specific member functions (inherited from PQ)
      const Data& Tip() const; // Override PQ member (throws std::length_error when empty)
      void RemoveTip(); // Override PQ member (throws std::length_error when empty)
      Data TipNRemove(); // Override PQ member (throws std::length_error when empty)
    
      void Insert(const Data&); // Override PQ member (Copy of the value)
      void Insert(Data&&) noexcept; // Override PQ member (Move of the value)
    
      void Change(ulong, const Data&); // Override PQ member (Copy of the value)
      void Change(ulong, Data&&) noexcept; // Override PQ member (Move of the value)

      // Specific member function (inherited from ClearableContainer)
      void Clear() noexcept override; // Override ClearableContainer member

      // Specific member function (inherited from LinearContainer)
      using LinearContainer<Data>::operator[];
      using LinearContainer<Data>::Front;
      using LinearContainer<Data>::Back;
    protected:
      // Auxiliary functions
      using HeapVec<Data>::Heapify; // Takes both functions
      void HeapifyUp(ulong, ulong) noexcept; // To bring a leaf node in the correct position

      void Resize(const ulong); // To correctly resize the heap
  };
}

#include "pqheap.cpp"

#endif