#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../container/linear.hpp"

namespace lasd {
  template <typename Data>
  class Vector: virtual public MutableLinearContainer<Data>, virtual public ResizableContainer {
    protected:
      using Container::size;
      Data* elements = nullptr;
    public:
      // Default constructor
      Vector() = default;

      // Specific constructors
      Vector(const ulong); // A vector with a given initial dimension
      Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer // Copy semantics
      Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer // Move semantics

      // Copy constructor
      Vector(const Vector&);

      // Move constructor
      Vector(Vector&&) noexcept;

      // Destructor
      virtual ~Vector();

      // Copy assignment
      Vector& operator = (const Vector&);

      // Move assignment
      Vector& operator = (Vector&&) noexcept;

      // Comparison operators
      bool operator == (const Vector&) const noexcept;
      inline bool operator != (const Vector&) const noexcept;

      // Specific member functions (inherited from MutableLinearContainer)
      Data& operator[] (const ulong) override; // Override MutableLinearContainer member (throws std::out_of_range when out of range)
      Data& Front() override; // Override MutableLinearContainer member (throws std::length_error when empty)
      Data& Back() override; // Override MutableLinearContainer member (throws std::length_error when empty)

      // Specific member functions (inherited from LinearContainer)
      const Data& operator[] (const ulong) const override; // Override LinearContainer member (throws std::out_of_range when out of range)
      const Data& Front() const override; // Override LinearContainer member (throws std::length_error when empty)
      const Data& Back() const override; // Override LinearContainer member (throws std::length_error when empty)

      // Specific member function (inherited from ResizableContainer)
      void Resize(const ulong) override; // Override ResizableContainer member

      // Specific member function (inherited from ClearableContainer)
      void Clear() noexcept override; // Override ClearableContainer member
  };

  template <typename Data>
  class SortableVector: virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {
    public:
      // Default constructor
      SortableVector() = default;

      // Specific constructors
      SortableVector(const ulong); // A vector with a given initial dimension
      SortableVector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer // Copy semantics
      SortableVector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer // Move semantics

      // Copy constructor
      SortableVector(const SortableVector&);

      // Move constructor
      SortableVector(SortableVector&&) noexcept;

      // Default destructor
      virtual ~SortableVector() = default;

      // Copy assignment
      SortableVector& operator = (const SortableVector&);

      // Move assignment
      SortableVector& operator = (SortableVector&&) noexcept;
  };
}

#include "vector.cpp"

#endif