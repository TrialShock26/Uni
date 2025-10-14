namespace lasd {
  template<typename Data>
  List<Data>::Node::Node(Data&& data) noexcept {
    std::swap(value, data);
  }

  template<typename Data>
  List<Data>::Node::Node(Node&& node) noexcept {
    std::swap(value, node.value);
    std::swap(next, node.next);
  }

  template<typename Data>
  List<Data>::Node::~Node() {
    delete next; // Recursively deleted
  }

  template<typename Data>
  bool List<Data>::Node::operator == (const Node& node) const noexcept {
    return (value == node.value) && ((next == nullptr && node.next == nullptr) || ((next != nullptr && node.next != nullptr) && (*next == *node.next)));
  }

  template<typename Data>
  bool List<Data>::Node::operator != (const Node& node) const noexcept {
    return !(*this == node);
  }

  template<typename Data>
  typename List<Data>::Node* List<Data>::Node::Clone(Node* leftover) {
    if (next == nullptr) {
      return leftover;
    }
    else {
      Node* tmpNode = new Node(value);
      tmpNode->next = next->Clone(leftover); // Clones all the nodes except the last one and attaches the leftover
      return tmpNode;
    }
  }

  template<typename Data>
  List<Data>::List(const TraversableContainer<Data>& inputC) {
    inputC.Traverse([this](const Data& data) {InsertAtBack(data);});
  }

  template<typename Data>
  List<Data>::List(MappableContainer<Data>&& inputC) {
    inputC.Map([this](Data& data) {InsertAtBack(std::move(data));});
  }

  template<typename Data>
  List<Data>::List(const List<Data>& inputL) {
    if (inputL.head != nullptr) {
      tail = new Node(*inputL.tail);
      head = inputL.head->Clone(tail);
      size = inputL.size;
    }
  }

  template<typename Data>
  List<Data>::List(List<Data>&& inputL) noexcept {
    std::swap(head, inputL.head);
    std::swap(tail, inputL.tail);
    std::swap(size, inputL.size);
  }

  template<typename Data>
  List<Data>::~List() {
    delete head; // Recursively deleted
  }

  template<typename Data>
  List<Data>& List<Data>::operator = (const List<Data>& right) {
    if (size <= right.size) {
      if (tail == nullptr) {
        List<Data>* tmpL = new List<Data>(right);
        std::swap(*tmpL, *this);
        delete tmpL;
      } 
      else {
        Node* rightCursor = right.head;
        for (Node* leftCursor = head; leftCursor != nullptr; leftCursor = leftCursor->next, rightCursor = rightCursor->next) {
          leftCursor->value = rightCursor->value;
        }
        if (rightCursor != nullptr) { // Size was less than right.size
          Node* newTail = new Node(*right.tail);
          tail->next = rightCursor->Clone(newTail);
          tail = newTail;
        }
      }
    } 
    else {
      if (right.tail == nullptr) {
        delete head;
        head = tail = nullptr;
      } 
      else {
        Node* leftCursor = head;                                    // Refreshes the tail each time with the correct one
        for (Node* rightCursor = right.head; rightCursor != nullptr; rightCursor = rightCursor->next, tail = leftCursor, leftCursor = leftCursor->next) {
          leftCursor->value = rightCursor->value;
        }
        delete leftCursor;
        tail->next = nullptr;
      }
    }
    size = right.size;
    return *this;
  }

  template<typename Data>
  List<Data>& List<Data>::operator = (List<Data>&& right) noexcept {
    std::swap(head, right.head);
    std::swap(tail, right.tail);
    std::swap(size, right.size);
    return *this;
  }

  template<typename Data>
  inline bool List<Data>::operator == (const List<Data>& right) const noexcept {
    return (size == right.size) && ((head == nullptr && right.head == nullptr) || ((head != nullptr && right.head != nullptr) && (*head == *right.head)));
  }

  template<typename Data>
  inline bool List<Data>::operator != (const List<Data>& right) const noexcept {
    return !(*this == right);
  }

  template<typename Data>
  void List<Data>::InsertAtFront(const Data& data) {
    AttachAtFront(new Node(data));
  }

  template<typename Data>
  void List<Data>::InsertAtFront(Data&& data) noexcept {
    AttachAtFront(new Node(std::move(data)));
  }

  template<typename Data>
  void List<Data>::RemoveFromFront() {
    delete DetachFront();
  }

  template<typename Data>
  Data List<Data>::FrontNRemove() {
    return DataNDelete(DetachFront());
  }

  template<typename Data>
  void List<Data>::InsertAtBack(const Data& data) {
    AttachAtBack(new Node(data));
  }

  template<typename Data>
  void List<Data>::InsertAtBack(Data&& data) noexcept {
    AttachAtBack(new Node(std::move(data)));
  }

  template<typename Data>
  void List<Data>::RemoveFromBack() {
    delete DetachBack();
  }

  template<typename Data>
  Data List<Data>::BackNRemove() {
    return DataNDelete(DetachBack());
  }

  template<typename Data>
  Data& List<Data>::operator[] (const ulong index) {
    if (index < size) {
      Node* cursor = head;
      for (ulong i = 0; i < index; i++, cursor = cursor->next) {}
      return cursor->value;
    } else {throw std::out_of_range("Index " + std::to_string(index) + " too large, list has only " + std::to_string(size) + " elements.");}
  }

  template<typename Data>
  inline Data& List<Data>::Front() {
    if (head != nullptr) {
      return head->value;
    } else {throw std::length_error("List is empty.");}
  }

  template<typename Data>
  inline Data& List<Data>::Back() {
    if (tail != nullptr) {
      return tail->value;
    } else {throw std::length_error("List is empty.");}
  }

  template<typename Data>
  const Data& List<Data>::operator[] (const ulong index) const {
    if (index < size) {
      Node* cursor = head;
      for (ulong i = 0; i < index; i++, cursor = cursor->next) {}
      return cursor->value;
    } else {throw std::out_of_range("Index " + std::to_string(index) + " too large, list has only " + std::to_string(size) + " elements.");}
  }

  template<typename Data>
  inline const Data& List<Data>::Front() const {
    if (head != nullptr) {
      return head->value;
    } else {throw std::length_error("List is empty.");}
  }

  template<typename Data>
  inline const Data& List<Data>::Back() const {
    if (tail != nullptr) {
      return tail->value;
    } else {throw std::length_error("List is empty.");}
  }

  template<typename Data>
  inline void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun, head);
  }

  template<typename Data>
  void List<Data>::PreOrderMap(MapFun fun) {
    PreOrderMap(fun, head);
  }

  template<typename Data>
  void List<Data>::PostOrderMap(MapFun fun) {
    PostOrderMap(fun, head);
  }

  template<typename Data>
  inline void List<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun, head);
  }

  template<typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun) const {
    PreOrderTraverse(fun, head);
  }

  template<typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun) const {
    PostOrderTraverse(fun, head);
  }

  template<typename Data>
  void List<Data>::Clear() noexcept {
    delete head;
    head = tail = nullptr;
    size = 0;
  }

  template<typename Data>
  void List<Data>::AttachAtFront(Node* node) noexcept {
    if (head != nullptr) {
      node->next = head;
      head = node;
    } else {head = tail = node;}
    size++;
  }
  template<typename Data>
  void List<Data>::AttachAtBack(Node* node) noexcept {
    if (tail != nullptr) {
      tail->next = node;
      tail = node;
    } else {head = tail = node;}
    size++;
  }

  template<typename Data>
  typename List<Data>::Node* List<Data>::DetachFront() {
    if (head != nullptr) {
      Node* toRet = head;
      head = head->next;
      toRet->next = nullptr;
      if (tail == toRet) {tail = head;}
      size--;
      return toRet;
    } else {throw std::length_error("List is empty.");}
  }

  template<typename Data>
  typename List<Data>::Node* List<Data>::DetachBack() {
    if (tail != nullptr) {
      Node* toRet = tail;
      if (head != tail) {
        Node* cursor = head;
        while (cursor->next != tail) {cursor = cursor->next;}
        tail = cursor;
        tail->next = nullptr;
      } else {head = tail = nullptr;}
      size--;
      return toRet;
    } else {throw std::length_error("List is empty.");}
  }

  template<typename Data>
  Data List<Data>::DataNDelete(Node* node) {
    Data toRet(std::move(node->value));
    delete node;
    return toRet;
  }

  template<typename Data>
  void List<Data>::PreOrderMap(MapFun fun, Node* current) {
    for (; current != nullptr; current = current->next) {
      fun(current->value);
    }
  }

  template<typename Data>
  void List<Data>::PostOrderMap(MapFun fun, Node* current) {
    if (current != nullptr) {
      PostOrderMap(fun, current->next);
      fun(current->value);
    }
  }

  template<typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun, Node* current) const {
    for (; current != nullptr; current = current->next) {
      fun(current->value);
    }
  }

  template<typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun, Node* current) const {
    if (current != nullptr) {
      PostOrderTraverse(fun, current->next);
      fun(current->value);
    }
  }
}