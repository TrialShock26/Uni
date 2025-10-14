#ifndef SETVEC_HPP
#define SETVEC_HPP

#include "../set.hpp"
#include "../../vector/vector.hpp"

#include <cmath>

namespace lasd {
  template <typename Data>
  class SetVec: virtual public Set<Data>, virtual protected Vector<Data> { // ADDED LATER: virtual could be omitted
    protected:
      using Vector<Data>::elements;
      using Container::size;
      ulong capacity = 0;

      ulong head = 0;
      ulong tail = 0;
    public:
      // Constructor
      SetVec() = default;
    
      // Specific constructors
      SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
      SetVec(MappableContainer<Data>&&); // A set obtained from a MappableContainer
    
      // Copy constructor
      SetVec(const SetVec&);
    
      // Move constructor
      SetVec(SetVec&&) noexcept;
    
      // Default destructor
      virtual ~SetVec() = default;
    
      // Copy assignment
      SetVec& operator = (const SetVec&);
    
      // Move assignment
      SetVec& operator = (SetVec&&) noexcept;
    
      // Comparison operators
      bool operator == (const SetVec&) const noexcept;
      inline bool operator != (const SetVec&) const noexcept;
    
      // Specific member functions (inherited from OrderedDictionaryContainer)
      const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      Data MinNRemove() override; // Overrideoverride OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
    
      const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
    
      const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
    
      const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
    
      // Specific member functions (inherited from DictionaryContainer)
      bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
      bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (move of the value)
      bool Remove(const Data&) override; // Override DictionaryContainer member
    
      // Specific member functions (inherited from LinearContainer)
      const Data& operator[] (const ulong) const override; // Override LinearContainer member (throws std::out_of_range when out of range)
      using Set<Data>::Front;
      using Set<Data>::Back;
    
      // Specific member function (inherited from TestableContainer)
      bool Exists(const Data&) const noexcept override; // Override TestableContainer member
    
      // Specific member function (inherited from ClearableContainer)
      void Clear() noexcept override; // Override ClearableContainer member
    protected:
      // Auxiliary functions
      void Resize(const ulong) override; // Override ResizableContainer member to correctly traverse the array

      void CheckEnlarge(); // Checks if the capacity has to be updated for the dynamic resizing
      void CheckReduce();

      ulong CreateHole(const ulong); // Shifts the elements right or left based on the pivot
      void RemoveHole(const ulong);

      ulong PredecessorIndex(const Data& data) const;
      ulong SuccessorIndex(const Data&) const;
  };
}

#include "setvec.cpp"

#endif