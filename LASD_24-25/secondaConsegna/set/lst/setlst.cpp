namespace lasd {
  template <typename Data>
  SetLst<Data>::SetLst(const TraversableContainer<Data>& inputC) {
    inputC.Traverse([this](const Data& data) {Insert(data);}); //A little inefficient, O(n²)
  }

  template <typename Data>
  SetLst<Data>::SetLst(MappableContainer<Data>&& inputC) {
    inputC.Map([this](const Data& data) {Insert(std::move(data));});
  }

  template <typename Data>
  SetLst<Data>::SetLst(const SetLst<Data>& inputS): List<Data>(inputS) {}

  template <typename Data>
  SetLst<Data>::SetLst(SetLst<Data>&& inputS) noexcept: List<Data>(std::move(inputS)) {}

  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator = (const SetLst<Data>& right) {
    List<Data>::operator = (right);
    return *this;
  }

  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator = (SetLst<Data>&& right) noexcept {
    List<Data>::operator = (std::move(right));
    return *this;
  }

  template <typename Data>
  inline bool SetLst<Data>::operator == (const SetLst<Data>& right) const noexcept {
    return List<Data>::operator == (right);
  }

  template <typename Data>
  inline bool SetLst<Data>::operator != (const SetLst<Data>& right) const noexcept {
    return !(*this == right);
  }

  template <typename Data>
  inline const Data& SetLst<Data>::Min() const {
    try {
      return List<Data>::Front();
    } catch (std::length_error& exc) {
      throw std::length_error("Set is empty.");
    }
  }

  template <typename Data>
  inline Data SetLst<Data>::MinNRemove() {
    try {
      return List<Data>::FrontNRemove();
    } catch (std::length_error& exc) {
      throw std::length_error("Set is empty.");
    }
  }

  template <typename Data>
  inline void SetLst<Data>::RemoveMin() {
    try {
      List<Data>::RemoveFromFront();
    } catch (std::length_error& exc) {
      throw std::length_error("Set is empty.");
    }
  }

  template <typename Data>
  inline const Data& SetLst<Data>::Max() const {
    try {
      return List<Data>::Back();
    } catch (std::length_error& exc) {
      throw std::length_error("Set is empty.");
    }
  }

  template <typename Data>
  inline Data SetLst<Data>::MaxNRemove() {
    try {
      return List<Data>::BackNRemove();
    } catch (std::length_error& exc) {
      throw std::length_error("Set is empty.");
    }
  }

  template <typename Data>
  inline void SetLst<Data>::RemoveMax() {
    try {
      List<Data>::RemoveFromBack();
    } catch (std::length_error& exc) {
      throw std::length_error("Set is empty.");
    }
  }

  template <typename Data>
  const Data& SetLst<Data>::Predecessor(const Data& data) const {
    Node* prev = nullptr;
    Node* cursor = head;
    while (cursor != nullptr && cursor->value < data) {
      prev = cursor;
      cursor = cursor->next;
    }
    if (prev != nullptr) {return prev->value;}
    else {throw std::length_error("Predecessor not found.");}
  }

  template <typename Data>
  Data SetLst<Data>::PredecessorNRemove(const Data& data) {
    Node* doublePrev = nullptr;
    Node* prev = nullptr;
    Node* cursor = head;
    while (cursor != nullptr && cursor->value < data) {
      doublePrev = prev;
      prev = cursor;
      cursor = cursor->next;
    }
    if (prev != nullptr) {
      Data toRet = std::move(prev->value);
      if (doublePrev != nullptr) {doublePrev->next = cursor;}
      else {head = cursor;}
      if (cursor == nullptr) {tail = doublePrev;}
      prev->next = nullptr;
      delete prev;
      size--;
      return toRet;
    }
    else {throw std::length_error("Predecessor not found.");}
  }

  template <typename Data>
  void SetLst<Data>::RemovePredecessor(const Data& data) {
    Node* doublePrev = nullptr;
    Node* prev = nullptr;
    Node* cursor = head;
    while (cursor != nullptr && cursor->value < data) {
      doublePrev = prev;
      prev = cursor;
      cursor = cursor->next;
    }
    if (prev != nullptr) {
      if (doublePrev != nullptr) {doublePrev->next = cursor;}
      else {head = cursor;}
      if (cursor == nullptr) {tail = doublePrev;}
      prev->next = nullptr;
      delete prev;
      size--;
    }
    else {throw std::length_error("Predecessor not found.");}
  }

  template <typename Data>
  const Data& SetLst<Data>::Successor(const Data& data) const {
    Node* cursor = head;
    while (cursor != nullptr && cursor->value <= data) {
      cursor = cursor->next;
    }
    if (cursor != nullptr) {
      return cursor->value;
    } else {throw std::length_error("Successor not found.");}
  }

  template <typename Data>
  Data SetLst<Data>::SuccessorNRemove(const Data& data) {
    Node* cursor = head;
    Node* prev = nullptr;
    while (cursor != nullptr && cursor->value <= data) {
      prev = cursor;
      cursor = cursor->next;
    }
    if (cursor != nullptr) {
      Data toRet = std::move(cursor->value);
      if (prev != nullptr) {
        prev->next = cursor->next;
        if (prev->next == nullptr) {tail = prev;}
      } else {
        head = cursor->next;
        if (head == nullptr) {tail = nullptr;}
      }
      cursor->next = nullptr;
      delete cursor;
      size--;
      return toRet;
    } else {throw std::length_error("Successor not found.");}
  }

  template <typename Data>
  void SetLst<Data>::RemoveSuccessor(const Data& data) {
    Node* cursor = head;
    Node* prev = nullptr;
    while (cursor != nullptr && cursor->value <= data) {
      prev = cursor;
      cursor = cursor->next;
    }
    if (cursor != nullptr) {
      if (prev != nullptr) {
        prev->next = cursor->next;
        if (prev->next == nullptr) {tail = prev;}
      } else {
        head = cursor->next;
        if (head == nullptr) {tail = nullptr;}
      }
      cursor->next = nullptr;
      delete cursor;
      size--;
    } else {throw std::length_error("Successor not found.");}
  }

  template <typename Data>
  bool SetLst<Data>::Insert(const Data& data) {
    Node* cursor = head;
    Node* prev = nullptr;
    while (cursor != nullptr && cursor->value < data) {
      prev = cursor;
      cursor = cursor->next;
    }
    if (cursor != nullptr && cursor->value == data) {return false;}
    Node* newNode = new Node(data);
    if (prev != nullptr) {
      prev->next = newNode;
      if (cursor == nullptr) {tail = newNode;}
    } else {
      head = newNode;
      if (tail == nullptr) {tail = newNode;}
    }
    newNode->next = cursor;
    size++;
    return true;
  }

  template <typename Data>
  bool SetLst<Data>::Insert(Data&& data) noexcept {
    Node* cursor = head;
    Node* prev = nullptr;
    while (cursor != nullptr && cursor->value < data) {
      prev = cursor;
      cursor = cursor->next;
    }
    if (cursor != nullptr && cursor->value == data) {return false;}
    Node* newNode = new Node(std::move(data));
    if (prev != nullptr) {
      prev->next = newNode;
      if (cursor == nullptr) {tail = newNode;}
    } else {
      head = newNode;
      if (tail == nullptr) {tail = newNode;}
    }
    newNode->next = cursor;
    size++;
    return true;
  }

  template <typename Data>
  bool SetLst<Data>::Remove(const Data& data) noexcept {
    Node* cursor = head;
    Node* prev = nullptr;
    while (cursor != nullptr && cursor->value < data) { // SWAPPED LATER
      prev = cursor;
      cursor = cursor->next;
    }
    if (cursor != nullptr && cursor->value == data) {
      if (prev != nullptr) {
        prev->next = cursor->next;
        if (cursor == tail) {
          tail = prev;
        }
      } else {
        head = cursor->next;
        if (cursor == tail) {tail = head;}
      }
      cursor->next = nullptr;
      delete cursor;
      size--;
      return true;
    } else {return false;}
  }

  template <typename Data>
  const Data& SetLst<Data>::operator[] (const ulong index) const {
    if (index < size) {
      Node* cursor = head;
      for (ulong i = 0; i < index; i++) {
        cursor = cursor->next;
      }
      return cursor->value;
    } else {throw std::out_of_range("Index " + std::to_string(index) + " too large, set has only " + std::to_string(size) + " elements.");}
  }

  template <typename Data>
  bool SetLst<Data>::Exists(const Data& data) const noexcept {
    Node* cursor = head;
    while (cursor != nullptr && cursor->value < data) {
      cursor = cursor->next;
    }
    if (cursor != nullptr && cursor->value == data) {return true;}
    else {return false;}
  }
}