namespace lasd {
  template <typename Data>
  PQHeap<Data>::PQHeap(const TraversableContainer<Data>& inputC): Vector<Data>::Vector(inputC), HeapVec<Data>::HeapVec(inputC) {
    capacity = size;
  }

  template <typename Data>
  PQHeap<Data>::PQHeap(MappableContainer<Data>&& inputC) noexcept: Vector<Data>::Vector(std::move(inputC)) {
    capacity = size;
    Heapify();
  }

  template <typename Data>
  PQHeap<Data>::PQHeap(const PQHeap<Data>& inputQ): Vector<Data>::Vector(), HeapVec<Data>::HeapVec() {
    size = inputQ.size;
    capacity = inputQ.capacity;
    elements = new Data[capacity];
    for (ulong i = 0; i < size; i++) {elements[i] = inputQ.elements[i];}
  }

  template <typename Data>
  PQHeap<Data>::PQHeap(PQHeap<Data>&& inputQ) noexcept {
    std::swap(size, inputQ.size);
    std::swap(capacity, inputQ.capacity);
    std::swap(elements, inputQ.elements);    
  }

  template <typename Data>
  PQHeap<Data>& PQHeap<Data>::operator = (const PQHeap<Data>& right) {
    PQHeap<Data>* tmpPQ = new PQHeap<Data>(right);
    std::swap(*tmpPQ, *this);
    delete tmpPQ;
    return *this;
  }

  template <typename Data>
  PQHeap<Data>& PQHeap<Data>::operator = (PQHeap<Data>&& right) noexcept {
    std::swap(size, right.size);
    std::swap(capacity, right.capacity);
    std::swap(elements, right.elements);
    return *this;
  }

  template <typename Data>
  inline bool PQHeap<Data>::operator == (const PQHeap<Data>& right) const noexcept {
    return Vector<Data>::operator == (right);
  }

  template <typename Data>
  inline bool PQHeap<Data>::operator != (const PQHeap<Data>& right) const noexcept {
    return Vector<Data>::operator != (right);
  }

  template <typename Data>
  const Data& PQHeap<Data>::Tip() const {
    if (size > 0) {
      return elements[0];
    } else {throw std::length_error("Priority queue is empty.");}
  }

  template <typename Data>
  void PQHeap<Data>::RemoveTip() {
    if (size > 0) {
      std::swap(elements[0], elements[size-1]);
      size--;
      Heapify(size, 0);
      if (size < capacity/2) {Resize(capacity/2);};
    } else {throw std::length_error("Priority queue is empty.");}
  }

  template <typename Data>
  Data PQHeap<Data>::TipNRemove() {
    if (size > 0) {
      Data toRet = std::move(elements[0]);
      std::swap(elements[0], elements[size-1]);
      size--;
      Heapify(size, 0);
      if (size < capacity/2) {Resize(capacity/2);};
      return toRet;
    } else {throw std::length_error("Priority queue is empty.");}
  }

  template <typename Data>
  void PQHeap<Data>::Insert(const Data& data) {
    if (capacity == 0) {Resize(4);}
    if (size+1 > capacity) {Resize(capacity*2);}
    elements[size] = data;
    size++;
    HeapifyUp(size, size-1);
  }

  template <typename Data>
  void PQHeap<Data>::Insert(Data&& data) noexcept {
    if (capacity == 0) {Resize(4);}
    if (size+1 > capacity) {Resize(capacity*2);}
    elements[size] = std::move(data);
    size++;
    HeapifyUp(size, size-1);
  }

  template <typename Data>
  void PQHeap<Data>::Change(ulong index, const Data& data) {
    if (index < size) {
      if (elements[index] < data) {
        elements[index] = data;
        HeapifyUp(size, index); // Fix upwards
      } else if (elements[index] > data) {
        elements[index] = data;
        Heapify(size, index); // Fix downwards
      } else {return;}
    }
  }

  template <typename Data>
  void PQHeap<Data>::Change(ulong index, Data&& data) noexcept {
    if (index < size) {
      if (elements[index] < data) {
        elements[index] = std::move(data);
        HeapifyUp(size, index); // Fix upwards
      } else if (elements[index] > data) {
        elements[index] = std::move(data);
        Heapify(size, index); // Fix downwards
      } else {return;}
    }
  }

  template<typename Data>
  void PQHeap<Data>::Clear() noexcept {
    HeapVec<Data>::Clear();
    capacity = 0;
  }

  template <typename Data>
  void PQHeap<Data>::HeapifyUp(ulong size, ulong index) noexcept {
    if (index != 0) {
      ulong p = static_cast<ulong>(floor((index-1)/2));
      if (elements[p] < elements[index]) {
        std::swap(elements[p], elements[index]);
        HeapifyUp(size, p);
      }
    } else {return;}
  }

  template<typename Data>
  void PQHeap<Data>::Resize(const ulong newCapacity) {
    if (newCapacity == 0) {Clear();}
    else if (capacity != newCapacity) {
      Data* tmpElements = new Data[newCapacity] {};
      for (ulong i = 0; i < size; i++) {
        std::swap(elements[i], tmpElements[i]);
      }
      std::swap(elements, tmpElements);
      capacity = newCapacity;
      delete[] tmpElements;
    }
  }
}