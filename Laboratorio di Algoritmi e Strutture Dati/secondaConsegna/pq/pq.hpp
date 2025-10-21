#ifndef PQ_HPP
#define PQ_HPP

#include "../container/linear.hpp"

namespace lasd {
  template <typename Data>
  class PQ: virtual public LinearContainer<Data>, virtual public ClearableContainer {
    public:    
      // Default destructor
      virtual ~PQ() = default;
    
      // Copy assignment
      PQ& operator = (const PQ&) = delete;
    
      // Move assignment
      PQ& operator = (PQ&&) noexcept = delete;
    
      // Specific member functions
      virtual const Data& Tip() const = 0; // (concrete function throws std::length_error when empty)
      virtual void RemoveTip() = 0; // (concrete function throws std::length_error when empty)
      virtual Data TipNRemove() = 0; // (concrete function throws std::length_error when empty)

      virtual void Insert(const Data&) = 0; // Copy of the value
      virtual void Insert(Data&&) noexcept = 0; // Move of the value

      virtual void Change(ulong, const Data&) = 0; // Copy of the value
      virtual void Change(ulong, Data&&) noexcept = 0; // Move of the value
  };
}

#endif