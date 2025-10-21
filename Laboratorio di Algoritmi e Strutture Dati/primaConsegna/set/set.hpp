#ifndef SET_HPP
#define SET_HPP

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"

namespace lasd {
  template <typename Data>
  class Set: virtual public OrderedDictionaryContainer<Data>, virtual public LinearContainer<Data>, virtual public ClearableContainer {
    public:
      // Destructor
      virtual ~Set() = default;

      // Copy assignment
      Set& operator = (const Set&) = delete;

      // Move assignment
      Set& operator = (Set&&) = delete;
    };
}

#endif