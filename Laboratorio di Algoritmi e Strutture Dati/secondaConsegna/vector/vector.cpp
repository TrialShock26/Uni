namespace lasd {
  template<typename Data>
  Vector<Data>::Vector(const ulong size) {
    this->size = size;
    elements = new Data[size] {};
  }

  template<typename Data>
  Vector<Data>::Vector(const TraversableContainer<Data>& inputC): Vector(inputC.Size()) {
    ulong index = 0;
    inputC.Traverse([this, &index](const Data& data) {elements[index++] = data;});
  }

  template<typename Data>
  Vector<Data>::Vector(MappableContainer<Data>&& inputC): Vector(inputC.Size()) {
    ulong index = 0;
    inputC.Map([this, &index](Data& data) {elements[index++] = std::move(data);});
  }

  template<typename Data>
  Vector<Data>::Vector(const Vector<Data>& inputV) {
    size = inputV.size;
    elements = new Data[size];
    for (ulong i = 0; i < size; i++) {elements[i] = inputV.elements[i];}
  }

  template<typename Data>
  Vector<Data>::Vector(Vector<Data>&& inputV) noexcept {
    std::swap(size, inputV.size);
    std::swap(elements, inputV.elements);
  }

  template<typename Data>
  Vector<Data>::~Vector() {
    delete[] elements;
  }

  template<typename Data>
  Vector<Data>& Vector<Data>::operator = (const Vector<Data>& right) {
    Vector<Data>* tmpVec = new Vector<Data>(right);
    std::swap(*tmpVec, *this);
    delete tmpVec;
    return *this;
  }

  template<typename Data>
  Vector<Data>& Vector<Data>::operator = (Vector<Data>&& right) noexcept {
    std::swap(size, right.size);
    std::swap(elements, right.elements);
    return *this;
  }

  template<typename Data>
  bool Vector<Data>::operator == (const Vector<Data>& right) const noexcept {
    if (size == right.size) {
      for (ulong i = 0; i < size; i++) {
        if (elements[i] != right.elements[i]) {
          return false;
        }
      }
      return true;
    } else {return false;}
  }

  template<typename Data>
  inline bool Vector<Data>::operator != (const Vector<Data>& right) const noexcept {
    return !(*this == right);
  }

  template<typename Data>
  Data& Vector<Data>::operator[] (const ulong index) {
    if (index < size) {
      return elements[index];
    } else {throw std::out_of_range("Index " + std::to_string(index) + " too large, vector has only " + std::to_string(size) + " elements.");}
  }

  template<typename Data>
  Data& Vector<Data>::Front() {
    if (size > 0) {
      return elements[0];
    } else {throw std::length_error("Vector is empty.");}
  }

  template<typename Data>
  Data& Vector<Data>::Back() {
    if (size > 0) {
      return elements[size-1];
    } else {throw std::length_error("Vector is empty.");}
  }

  template<typename Data>
  const Data& Vector<Data>::operator[] (const ulong index) const {
    if (index < size) {
      return elements[index];
    } else {throw std::out_of_range("Index " + std::to_string(index) + " too large, vector has only " + std::to_string(size) + " elements.");}
  }

  template<typename Data>
  const Data& Vector<Data>::Front() const {
    if (size > 0) {
      return elements[0];
    } else {throw std::length_error("Vector is empty.");}
  }

  template<typename Data>
  const Data& Vector<Data>::Back() const {
    if (size > 0) {
      return elements[size-1];
    } else {throw std::length_error("Vector is empty.");}
  }

  template<typename Data>
  void Vector<Data>::Resize(const ulong newSize) {
    if (newSize == 0) {Clear();}
    else if (size != newSize) {
      Data* tmpElements = new Data[newSize] {};
      ulong smallerSize;
      if (size < newSize) {smallerSize = size;}
      else {smallerSize = newSize;}
      for (ulong i = 0; i < smallerSize; i++) {
        std::swap(elements[i], tmpElements[i]);
      }
      std::swap(elements, tmpElements);
      size = newSize;
      delete[] tmpElements;
    }
  }

  template<typename Data>
  void Vector<Data>::Clear() noexcept {
    delete[] elements;
    elements = nullptr;
    size = 0;
  }

  template<typename Data>
  SortableVector<Data>::SortableVector(const ulong size): Vector<Data>(size) {}

  template<typename Data>
  SortableVector<Data>::SortableVector(const TraversableContainer<Data>& inputC): Vector<Data>(inputC) {}

  template<typename Data>
  SortableVector<Data>::SortableVector(MappableContainer<Data>&& inputC): Vector<Data>(std::move(inputC)) {}

  template<typename Data>
  SortableVector<Data>::SortableVector(const SortableVector<Data>& inputV): Vector<Data>(inputV) {}

  template<typename Data>
  SortableVector<Data>::SortableVector(SortableVector<Data>&& inputV) noexcept: Vector<Data>(std::move(inputV)) {}

  template<typename Data>
  SortableVector<Data>& SortableVector<Data>::operator = (const SortableVector<Data>& right) {
    Vector<Data>::operator = (right);
    return *this;
  }

  template<typename Data>
  SortableVector<Data>& SortableVector<Data>::operator = (SortableVector<Data>&& right) noexcept {
    Vector<Data>::operator = (std::move(right));
    return *this;
  }
}