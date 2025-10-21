namespace lasd {
  template <typename Data>
  inline bool LinearContainer<Data>::operator == (const LinearContainer& right) const noexcept {
    if (size == right.size) {
      for (ulong idx = 0; idx < size; idx++) {
        if (operator[](idx) != right.operator[](idx)) {return false;}
      }
      return true;
    } else {return false;}
  }

  template <typename Data>
  inline bool LinearContainer<Data>::operator != (const LinearContainer& right) const noexcept {
    return !(*this == right);
  }

  template <typename Data>
  inline const Data& LinearContainer<Data>::Front() const {
    return operator[](0);
  }

  template <typename Data>
  inline const Data& LinearContainer<Data>::Back() const {
    return operator[](size-1);
  }

  template <typename Data>
  inline void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
  }

  template <typename Data>
  inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
    for (ulong idx = 0; idx < size; idx++) {
      fun(operator[](idx));
    }
  }

  template <typename Data>
  inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
    ulong idx = size;
    while (idx > 0) {
      fun(operator[](--idx));
    }
  }

  template <typename Data>
  inline Data& MutableLinearContainer<Data>::Front() {
    return operator[](0);
  }

  template <typename Data>
  inline Data& MutableLinearContainer<Data>::Back() {
    return operator[](size-1);
  }

  template <typename Data>
  inline void MutableLinearContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
  }

  template <typename Data>
  inline void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
    for (ulong idx = 0; idx < size; idx++) {
      fun(operator[](idx));
    }
  }

  template <typename Data>
  inline void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
    ulong idx = size;
    while (idx > 0) {
      fun(operator[](--idx));
    }
  }

  template <typename Data>
  void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r) noexcept {
    if (p < r) {
      ulong q = Partition(p, r);
      QuickSort(p, q);
      QuickSort(q+1, r);
    }
  }

  template <typename Data>
  ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept {
    const Data& x = this->operator[](p);
    ulong i = p-1, j = r+1;
    do {
      do {
        j--;
      } while(this->operator[](j) > x);
      do {
        i++;
      } while(this->operator[](i) < x);
      if (i < j) {
        std::swap(this->operator[](i), this->operator[](j));
      }
    } while(j > i);
    return j;
  }

  template <typename Data>
  void SortableLinearContainer<Data>::Sort() noexcept {
    QuickSort(0, size-1);
  }
}