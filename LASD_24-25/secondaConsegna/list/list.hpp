#ifndef LIST_HPP
#define LIST_HPP

#include "../container/linear.hpp"

namespace lasd {
  template <typename Data>
  class List: virtual public MutableLinearContainer<Data>, virtual public ClearableContainer {
    protected:
      using Container::size;

      struct Node {
        Data value;
        Node* next = nullptr;

        // Specific constructors
        Node() = default;
        Node(const Data& data): value(data) {};
        Node(Data&&) noexcept;

        // Copy constructor
        Node(const Node& node): value(node.value) {};

        // Move constructor
        Node(Node&&) noexcept;

        // Destructor
        virtual ~Node();

        // Comparison operators
        bool operator == (const Node&) const noexcept;
        inline bool operator != (const Node&) const noexcept;

        // Specific member functions
        virtual Node* Clone(Node*); // Deep copy
      };

      Node* head = nullptr;
      Node* tail = nullptr;
    public:
      // Default constructor
      List() = default;

      // Specific constructor
      List(const TraversableContainer<Data>&); // A list obtained from a TraversableContainer // Copy semantics
      List(MappableContainer<Data>&&); // A list obtained from a MappableContainer //Move semantics

      // Copy constructor
      List(const List&);

      // Move constructor
      List(List&&) noexcept;

      // Destructor
      virtual ~List();

      // Copy assignment
      List& operator = (const List&);

      // Move assignment
      List& operator = (List&&) noexcept;

      // Comparison operators
      inline bool operator == (const List&) const noexcept;
      inline bool operator != (const List&) const noexcept;

      // Specific member functions
      void InsertAtFront(const Data&); // Copy of the value
      void InsertAtFront(Data&&) noexcept; // Move of the value
      void RemoveFromFront(); // (throws std::length_error when empty)
      Data FrontNRemove(); // (throws std::length_error when empty)

      void InsertAtBack(const Data&); // Copy of the value
      void InsertAtBack(Data&&) noexcept; // Move of the value
      void RemoveFromBack(); // (throws std::length_error when empty)
      Data BackNRemove(); // (throws std::length_error when empty)

      // Specific member functions (inherited from MutableLinearContainer)
      Data& operator[] (const ulong) override; // Override MutableLinearContainer member (throws std::out_of_range when out of range)
      inline Data& Front() override; // Override MutableLinearContainer member (throws std::length_error when empty)
      inline Data& Back() override; // Override MutableLinearContainer member (throws std::length_error when empty)

      // Specific member functions (inherited from LinearContainer)
      const Data& operator[] (const ulong) const override; // Override LinearContainer member (throws std::out_of_range when out of range)
      inline const Data& Front() const override; // Override LinearContainer member (throws std::length_error when empty)
      inline const Data& Back() const override; // Override LinearContainer member (throws std::length_error when empty)

      // Specific member function (inherited from MappableContainer)
      using typename MappableContainer<Data>::MapFun;

      inline void Map(MapFun) override; // Override MappableContainer member

      // Specific member function (inherited from PreOrderMappableContainer)
      void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

      // Specific member function (inherited from PostOrderMappableContainer)
      void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

      // Specific member function (inherited from TraversableContainer)
      using typename TraversableContainer<Data>::TraverseFun;

      inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

      // Specific member function (inherited from PreOrderTraversableContainer)
      void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

      // Specific member function (inherited from PostOrderTraversableContainer)
      void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

      // Specific member function (inherited from ClearableContainer)
      void Clear() noexcept override; // Override ClearableContainer member
    protected:
      // Auxiliary functions
      void AttachAtFront(Node*) noexcept;
      void AttachAtBack(Node*) noexcept;

      Node* DetachFront();
      Node* DetachBack();

      Data DataNDelete(Node*);

      void PreOrderMap(MapFun, Node*);
      void PostOrderMap(MapFun, Node*);

      void PreOrderTraverse(TraverseFun, Node*) const;
      void PostOrderTraverse(TraverseFun, Node*) const; //Working on the single nodes
  };
}

#include "list.cpp"

#endif
