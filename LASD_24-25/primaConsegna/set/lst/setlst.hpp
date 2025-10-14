#ifndef SETLST_HPP
#define SETLST_HPP

#include "../set.hpp"
#include "../../list/list.hpp"

namespace lasd {
  template <typename Data>
  class SetLst: virtual public Set<Data>, virtual protected List<Data> {
    protected:
      using Container::size;
      using typename List<Data>::Node;
      using List<Data>::head;
      using List<Data>::tail;
    public:
      // Default constructor
      SetLst() = default;

      // Specific constructors
      SetLst(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer //Copy semantics
      SetLst(MappableContainer<Data>&&); // A set obtained from a MappableContainer //Move semantics

      // Copy constructor
      SetLst(const SetLst&);

      // Move constructor
      SetLst(SetLst&&) noexcept;

      // Default destructor
      virtual ~SetLst() = default;

      // Copy assignment
      SetLst& operator = (const SetLst&);

      // Move assignment
      SetLst& operator = (SetLst&&) noexcept;

      // Comparison operators
      inline bool operator == (const SetLst&) const noexcept;
      inline bool operator != (const SetLst&) const noexcept;

      // Specific member functions (inherited from OrderedDictionaryContainer)
      inline const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      inline Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      inline void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)

      inline const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      inline Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)
      inline void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when empty)

      const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)

      const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)
      void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function throws std::length_error when not found)

      // Specific member functions (inherited from DictionaryContainer)
      bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
      bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (move of the value)
      bool Remove(const Data&) noexcept override; // Override DictionaryContainer member

      // Specific member functions (inherited from LinearContainer)
      const Data& operator[] (const ulong) const override; // Override LinearContainer member (throws std::out_of_range when out of range)
      using Set<Data>::Traverse;
      using Set<Data>::PreOrderTraverse;
      using Set<Data>::PostOrderTraverse;

      // Specific member function (inherited from TestableContainer)
      bool Exists(const Data&) const noexcept override; // Override TestableContainer member

      // Specific member function (inherited from ClearableContainer)
      void Clear() override; // Override ClearableContainer member
  };
}

#include "setlst.cpp"

#endif