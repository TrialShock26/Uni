#ifndef LINEAR_HPP
#define LINEAR_HPP

#include "mappable.hpp"

namespace lasd {
  template <typename Data>
  class LinearContainer: virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data> {
    protected:
      using Container::size;
    public:
      // Destructor
      virtual ~LinearContainer() = default;

      // Copy assignment
      LinearContainer& operator = (const LinearContainer&) = delete;

      // Move assignment
      LinearContainer& operator = (LinearContainer&&) noexcept = delete;

      // Comparison operators
      inline bool operator == (const LinearContainer&) const noexcept;
      inline bool operator != (const LinearContainer&) const noexcept;

      // Specific member functions
      virtual const Data& operator[] (ulong) const = 0; // (non-mutable version; concrete function throws std::out_of_range when out of range)
      inline virtual const Data& Front() const; // (non-mutable version; concrete function throws std::length_error when empty)
      inline virtual const Data& Back() const; // (non-mutable version; concrete function throws std::length_error when empty)

      // Specific member function (inherited from TraversableContainer)
      using typename TraversableContainer<Data>::TraverseFun;

      inline void Traverse(TraverseFun) const override; // Override TraversableContainer member //Defaults to PreOrderTraverse

      // Specific member function (inherited from PreOrderTraversableContainer)
      inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

      // Specific member function (inherited from PostOrderTraversableContainer)
      inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member
  };

  template <typename Data>
  class MutableLinearContainer: virtual public LinearContainer<Data>, virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data> {
    protected:
      using Container::size;
    public:
      // Destructor
      virtual ~MutableLinearContainer() = default;

      // Copy assignment
      MutableLinearContainer& operator = (const MutableLinearContainer&) = delete;

      // Move assignment
      MutableLinearContainer& operator = (MutableLinearContainer&&) noexcept = delete;

      // Specific member functions
      using LinearContainer<Data>::operator[];
      using LinearContainer<Data>::Front;
      using LinearContainer<Data>::Back;

      virtual Data& operator[] (ulong) = 0; // (mutable version; concrete function throws std::out_of_range when out of range)
      inline virtual Data& Front(); // (mutable version; concrete function throws std::length_error when empty)
      inline virtual Data& Back(); // (mutable version; concrete function throws std::length_error when empty)

      // Specific member function (inherited from MappableContainer)
      using typename MappableContainer<Data>::MapFun;

      inline void Map(MapFun) override; // Override MappableContainer member

      // Specific member function (inherited from PreOrderMappableContainer)
      inline void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

      // Specific member function (inherited from PostOrderMappableContainer)
      inline void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  };

  template <typename Data>
  class SortableLinearContainer: virtual public MutableLinearContainer<Data> {
    protected:
      using Container::size;
      
      // Auxiliary member functions
      void QuickSort(ulong, ulong) noexcept;
      ulong Partition(ulong, ulong) noexcept;
    public:
      // Destructor
      virtual ~SortableLinearContainer() = default;

      // Copy assignment
      SortableLinearContainer& operator = (const SortableLinearContainer&) = delete;

      // Move assignment
      SortableLinearContainer& operator = (SortableLinearContainer&&) noexcept = delete;

      // Specific member function
      virtual void Sort() noexcept;
  };
}

#include "linear.cpp"

#endif