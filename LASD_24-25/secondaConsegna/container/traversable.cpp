namespace lasd {
  template <typename Data>
  template <typename Accumulator>
  inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const {
    Traverse([fun, &acc](const Data& data) {acc = fun(data, acc);});
    return acc;
  }

  template <typename Data>
  inline bool TraversableContainer<Data>::Exists(const Data& target) const noexcept {
    bool exists = false;
    Traverse([&exists, target](const Data& data) {exists |= data == target;});
    return exists;
  }

  template <typename Data>
  template <typename Accumulator>
  inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    PreOrderTraverse([fun, &acc](const Data& data) {acc = fun(data, acc);});
    return acc;
  }

  template <typename Data>
  inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
  }

  template <typename Data>
  template <typename Accumulator>
  inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    PostOrderTraverse([fun, &acc](const Data& data) {acc = fun(data, acc);});
    return acc;
  }
  
  template <typename Data>
  inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PostOrderTraverse(fun);
  }
}