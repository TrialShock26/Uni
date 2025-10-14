namespace lasd {
  template <typename Data>
  SetVec<Data>::SetVec(const TraversableContainer<Data>& inputC) {
    inputC.Traverse([this](const Data& data) {Insert(data);});
  }

  template <typename Data>
  SetVec<Data>::SetVec(MappableContainer<Data>&& inputC) {
    inputC.Map([this](const Data& data) {Insert(std::move(data));});
  }

  template <typename Data>
  SetVec<Data>::SetVec(const SetVec<Data>& inputS) {
    size = inputS.size;
    capacity = inputS.capacity;
    elements = new Data[capacity];
    head = inputS.head;
    tail = inputS.tail;
    for (ulong i = 0; i < size; i++) {elements[(head + i) % capacity] = inputS.elements[(head + i) % capacity];}
  }

  template <typename Data>
  SetVec<Data>::SetVec(SetVec<Data>&& inputS) noexcept {
    std::swap(size, inputS.size);
    std::swap(capacity, inputS.capacity);
    std::swap(head, inputS.head);
    std::swap(tail, inputS.tail);
    std::swap(elements, inputS.elements);
  }

  template <typename Data>
  SetVec<Data>& SetVec<Data>::operator = (const SetVec<Data>& right) {
    SetVec<Data>* tmpSet = new SetVec<Data>(right);
    std::swap(*tmpSet, *this);
    delete tmpSet;
    return *this;
  }

  template <typename Data>
  SetVec<Data>& SetVec<Data>::operator = (SetVec<Data>&& right) noexcept {
    std::swap(size, right.size);
    std::swap(capacity, right.capacity);
    std::swap(head, right.head);
    std::swap(tail, right.tail);
    std::swap(elements, right.elements);
    return *this;
  }

  template <typename Data>
  bool SetVec<Data>::operator == (const SetVec<Data>& right) const noexcept {
    if (size == right.size) {
      for (ulong i = 0; i < size; i++) {
        if (elements[(head + i) % capacity] != right.elements[(right.head + i) % right.capacity]) {
          return false;
        }
      }
      return true;
    } else {return false;}
  }

  template <typename Data>
  inline bool SetVec<Data>::operator != (const SetVec<Data>& right) const noexcept {
    return !(*this == right);
  }

  template <typename Data>
  const Data& SetVec<Data>::Min() const {
    if (size > 0) {
      return elements[head];
    } else {throw std::length_error("Set is empty.");}
  }

  template <typename Data>
  Data SetVec<Data>::MinNRemove() {
    if (size > 1) {
      Data toRet = elements[head];
      head = (head+1) % capacity;
      CheckReduce();
      size--;
      return toRet;
    } else if (size == 1) {
      CheckReduce();
      size--;
      tail = head;
      return elements[head];
    } else {throw std::length_error("Set is empty.");}
  }

  template <typename Data>
  void SetVec<Data>::RemoveMin() {
    if (size > 1) {
      head = (head+1) % capacity;
      CheckReduce();
      size--;
    } else if (size == 1) {
      CheckReduce();
      size--;
      tail = head;
    } else {throw std::length_error("Set is empty.");}
  }

  template <typename Data>
  const Data& SetVec<Data>::Max() const {
    if (size > 0) {
      return elements[(tail + capacity - 1) % capacity];
    } else {throw std::length_error("Set is empty.");}
  }

  template <typename Data>
  Data SetVec<Data>::MaxNRemove() {
    if (size > 1) {
      tail = (tail + capacity - 1) % capacity;
      Data toRet = elements[tail];
      CheckReduce();
      size--;
      return toRet;
    } else if (size == 1) {
      CheckReduce();
      size--;
      tail = head;
      return elements[tail];
    } else {throw std::length_error("Set is empty.");}
  }

  template <typename Data>
  void SetVec<Data>::RemoveMax() {
    if (size > 1) {
      tail = (tail + capacity - 1) % capacity;
      CheckReduce();
      size--;
    } else if (size == 1) {
      CheckReduce();
      size--;
      tail = head;
    } else {throw std::length_error("Set is empty.");}
  }

  template <typename Data>
  const Data& SetVec<Data>::Predecessor(const Data& data) const {
    ulong predecessor = PredecessorIndex(data);
    if (predecessor != tail) {return elements[predecessor];}
    else {throw std::length_error("Predecessor not found.");}
  }

  template <typename Data>
  Data SetVec<Data>::PredecessorNRemove(const Data& data) {
    ulong predecessor = PredecessorIndex(data);
    if (predecessor != tail) {
      Data toRet = elements[predecessor];
      RemoveHole(predecessor);
      return toRet;
    }
    else {throw std::length_error("Predecessor not found.");}
  }

  template <typename Data>
  void SetVec<Data>::RemovePredecessor(const Data& data) {
    ulong predecessor = PredecessorIndex(data);
    if (predecessor != tail) {RemoveHole(predecessor);}
    else {throw std::length_error("Predecessor not found.");}
  }

  template <typename Data>
  const Data& SetVec<Data>::Successor(const Data& data) const {
    ulong successor = SuccessorIndex(data);
    if (successor != tail) {return elements[successor];}
    else {throw std::length_error("Successor not found.");}
  }

  template <typename Data>
  Data SetVec<Data>::SuccessorNRemove(const Data& data) {
    ulong successor = SuccessorIndex(data);
    if (successor != tail) {
      Data toRet = elements[successor];
      RemoveHole(successor);
      return toRet;
    }
    else {throw std::length_error("Successor not found.");}
  }

  template <typename Data>
  void SetVec<Data>::RemoveSuccessor(const Data& data) {
    ulong successor = SuccessorIndex(data);
    if (successor != tail) {RemoveHole(successor);}
    else {throw std::length_error("Successor not found.");}
  }

  template <typename Data>
  bool SetVec<Data>::Insert(const Data& data) {
    CheckEnlarge();
    ulong i = head, j = tail, k, treatedSize;
    while ((j + capacity - i) % capacity > 0) { // Binary search
      treatedSize = (j + capacity - i) % capacity; // The number of elements to consider
      k = (i + static_cast<ulong>(floor(treatedSize / 2))) % capacity; // floor() is not needed, there for clarity, safe to cast the result from double to ulong
      if (elements[k] > data) {j = k;}
      else if (elements[k] < data) {i = (k+1) % capacity;}
      else {return false;}
    }
    if (j == tail) {
      elements[tail] = data;
      tail = (tail+1) % capacity;
    } else if (j == head) {
      head = (head + capacity - 1) % capacity;
      elements[head] = data;
    } else {
      j = CreateHole(j);
      elements[j] = data;
    }
    size++;
    return true;
  }

  template <typename Data>
  bool SetVec<Data>::Insert(Data&& data) noexcept {
    CheckEnlarge();
    ulong i = head, j = tail, k, treatedSize;
    while ((j + capacity - i) % capacity > 0) { // Binary search
      treatedSize = (j + capacity - i) % capacity; // The number of elements to consider
      k = (i + static_cast<ulong>(floor(treatedSize / 2))) % capacity; // floor() is not needed, there for clarity, safe to cast the result from double to ulong
      if (elements[k] > data) {j = k;}
      else if (elements[k] < data) {i = (k+1) % capacity;}
      else {return false;}
    }
    if (j == tail) {
      elements[tail] = std::move(data);
      tail = (tail+1) % capacity;
    } else if (j == head) {
      head = (head + capacity - 1) % capacity;
      elements[head] = std::move(data);
    } else {
      j = CreateHole(j);
      elements[j] = std::move(data);
    }
    size++;
    return true;
  }

  template <typename Data>
  bool SetVec<Data>::Remove(const Data& data) {
    if (size > 0) {
      ulong i = head, j = tail, k, treatedSize;
      bool found = false;
      while ((found == false) && ((j + capacity - i) % capacity > 0)) {
        treatedSize = (j + capacity - i) % capacity; // the number of elements I need to consider
        k = (i + static_cast<ulong>(floor(treatedSize / 2))) % capacity; // floor() is not needed, there for clarity, safe to cast the result from double to ulong
        if (elements[k] > data) {j = k;}
        else if (elements[k] < data) {i = (k+1) % capacity;}
        else {found = true;}
      }
      if (found == true) {
        RemoveHole(k);
        return true;
      } else {return false;}
    } else {throw std::length_error("Set is empty.");}
  }

  template <typename Data>
  const Data& SetVec<Data>::operator[] (const ulong index) const {
    if (index < size) {
      return elements[(head + index) % capacity];
    } else {throw std::out_of_range("Index " + std::to_string(index) + " too large, set has only " + std::to_string(size) + " elements.");}
  }

  template <typename Data>
  bool SetVec<Data>::Exists(const Data& data) const noexcept {
    if (size > 0) {
      ulong i = head, j = tail, k, treatedSize;
      while ((j + capacity - i) % capacity > 0) {
        treatedSize = (j + capacity - i) % capacity; // the number of elements I need to consider
        k = (i + static_cast<ulong>(floor(treatedSize / 2))) % capacity; // floor() is not needed, there for clarity, safe to cast the result from double to ulong
        if (elements[k] > data) {j = k;}
        else if (elements[k] < data) {i = (k+1) % capacity;}
        else {return true;}
      }
      return false;
    } else {return false;}
  }

  template <typename Data>
  void SetVec<Data>::Clear() {
    Vector<Data>::Clear();
    capacity = 0;
    head = tail = 0;
  }

  template <typename Data>
  void SetVec<Data>::Resize(const ulong newCapacity) {
    if (newCapacity == 0) {Clear();}
    else if (capacity != newCapacity) {
      Data* tmpElements = new Data[newCapacity] {};
      for (ulong i = 0; i < size; i++) {
        std::swap(elements[(head + i) % capacity], tmpElements[i]);
      }
      std::swap(elements, tmpElements);
      capacity = newCapacity;
      head = 0;
      tail = size;
      delete[] tmpElements;
    }
  }

  template <typename Data>
  void SetVec<Data>::CheckEnlarge() {
    if (size != 0 && (size+1) >= (capacity*0.7)) {
      Resize(capacity*2);
    } else if (size == 0) {Resize(4);} // Fixed starting point cells
  }

  template <typename Data>
  void SetVec<Data>::CheckReduce() {
    if (size != 0 && (size-1) <= (capacity*0.3)) {
      size--; // This is added to keep the Resize() method general
      Resize(capacity/2);
      size++;
    }
  }

  template <typename Data>
  ulong SetVec<Data>::CreateHole(const ulong pivot) {
    ulong sizeRight = (tail + capacity - pivot) % capacity, sizeLeft = (pivot + capacity - head) % capacity;
    if (sizeLeft >= sizeRight) {
      ulong index = tail;
      tail = (tail+1) % capacity;
      for (; index != pivot; index = (index + capacity - 1) % capacity) { // Shift right
        elements[index] = elements[(index + capacity - 1) % capacity];
      }
      return pivot;
    } else {
      head = (head + capacity - 1) % capacity;
      ulong newPivot = (pivot + capacity - 1) % capacity;
      for (ulong index = head; index != newPivot; index = (index+1) % capacity) {  // Shift left
        elements[index] = elements[(index+1) % capacity];
      }
      return newPivot;
    }
  }

  template <typename Data>
  void SetVec<Data>::RemoveHole(const ulong pivot) {
    if (pivot == head) {RemoveMin();}
    else if (pivot == (tail + capacity - 1) % capacity) {RemoveMax();}
    else {
      ulong sizeRight = (tail + capacity - pivot) % capacity, sizeLeft = (pivot + capacity - head) % capacity;
      if (sizeLeft >= sizeRight-1) { // -1 to exclude pivot
        tail = (tail + capacity - 1) % capacity;
        for (ulong index = pivot; index != tail; index = (index+1) % capacity) { // Shift the right side to left
          elements[index] = elements[(index+1) % capacity];
        }
      } else {
        for (ulong index = pivot; index != head; index = (index + capacity - 1) % capacity) { // Shift the left side to right
          elements[index] = elements[(index + capacity - 1) % capacity];
        }
        head = (head+1) % capacity;
      }
      CheckReduce();
      size--;
    }
  }

  template <typename Data>
  ulong SetVec<Data>::PredecessorIndex(const Data& data) const {
    if (size > 0) {
      ulong i = head, j = tail, k, treatedSize, s = tail;
      while ((j + capacity - i) % capacity > 0) { // Binary search
        treatedSize = (j + capacity - i) % capacity; // The number of elements to consider
        k = (i + static_cast<ulong>(floor(treatedSize / 2))) % capacity; // floor() is not needed, there for clarity, safe to cast the result from double to ulong
        if (elements[k] < data) { // Flipped condition to look for the predecessor
          i = (k+1) % capacity;
          s = k;
        }
        else {j = k;}
      }
      return s;
    } else {return tail;}
  }

  template <typename Data>
  ulong SetVec<Data>::SuccessorIndex(const Data& data) const {
    if (size > 0) {
      ulong i = head, j = tail, k, treatedSize;
      while ((j + capacity - i) % capacity > 0) { // Binary search
        treatedSize = (j + capacity - i) % capacity; // The number of elements to consider
        k = (i + static_cast<ulong>(floor(treatedSize / 2))) % capacity; // floor() is not needed, there for clarity, safe to cast the result from double to ulong
        if (elements[k] > data) {j = k;}
        else {i = (k+1) % capacity;}
      }
      return j;
    } else {return tail;}
  }
}