namespace lasd {
  template <typename Data>
  HeapVec<Data>::HeapVec(const TraversableContainer<Data>& inputC): Vector<Data>::Vector(inputC) {
    Heapify();
  }

  template <typename Data>
  HeapVec<Data>::HeapVec(MappableContainer<Data>&& inputC) noexcept: Vector<Data>::Vector(std::move(inputC)) {
    Heapify();
  }

  template <typename Data>
  HeapVec<Data>::HeapVec(const HeapVec<Data>& inputH): Vector<Data>::Vector(inputH) {}

  template <typename Data>
  HeapVec<Data>::HeapVec(HeapVec<Data>&& inputH) noexcept: Vector<Data>::Vector(std::move(inputH)) {}

  template <typename Data>
  HeapVec<Data>& HeapVec<Data>::operator = (const HeapVec<Data>& right) {
    Vector<Data>::operator = (right);
    return *this;
  }
  
  template <typename Data>
  HeapVec<Data>& HeapVec<Data>::operator = (HeapVec<Data>&& right) noexcept {
    Vector<Data>::operator = (std::move(right));
    return *this;
  }

  template <typename Data>
  inline bool HeapVec<Data>::operator == (const HeapVec<Data>& right) const noexcept {
    return Vector<Data>::operator == (right);
  }

  template <typename Data>
  inline bool HeapVec<Data>::operator != (const HeapVec<Data>& right) const noexcept {
    return Vector<Data>::operator != (right);
  }

  template <typename Data>
  bool HeapVec<Data>::IsHeap() const noexcept {
    ulong halfSize = static_cast<ulong>(floor(size/2)); // Other half of the array is made up of leaves
    for (ulong i = 1; i < halfSize; i++) {
      if (elements[i-1] < elements[2*(i-1) + 1] || elements[i-1] < elements[2*(i-1) + 2]) {return false;}
    }
    return true;
  }

  template <typename Data>
  inline void HeapVec<Data>::Heapify() noexcept {
    // Builds a MaxHeap
    // Call to IsHeap() not needed, useless overhead
    ulong halfSize = static_cast<ulong>(floor(size/2)); // Other half of the array is made up of leaves
    for (ulong i = halfSize; i > 0; i--) {
      Heapify(size, i-1);
    }
  }

  template <typename Data>
  inline void HeapVec<Data>::Sort() noexcept {HeapSort();}

  template <typename Data>
  void HeapVec<Data>::Heapify(ulong size, ulong index) noexcept {
    ulong m = index, l = index*2 + 1, r = index*2 + 2;
    if (l < size && elements[m] < elements[l]) {m = l;}
    if (r < size && elements[m] < elements[r]) {m = r;}
    if (m != index) {
      std::swap(elements[m], elements[index]);
      Heapify(size, m);
    }
  }

  template <typename Data>
  void HeapVec<Data>::HeapSort() noexcept {
    Heapify();
    for (ulong i = size; i > 1; i--) {
      std::swap(elements[0], elements[i-1]);
      Heapify(i-1, 0);
    }
  }
}