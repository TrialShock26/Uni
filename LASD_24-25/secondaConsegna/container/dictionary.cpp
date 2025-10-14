namespace lasd {
  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& inputC) {
    bool allInserted = true;
    inputC.Traverse([&allInserted, this](const Data& data) {allInserted &= Insert(data);});
    return allInserted;
  }

  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& inputC) {
    bool allInserted = true;
    inputC.Map([&allInserted, this](Data& data) {allInserted &= Insert(std::move(data));});
    return allInserted;
  }

  template <typename Data>
  inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& inputC) {
    bool allRemoved = true;
    inputC.Traverse([&allRemoved, this](const Data& data) {allRemoved &= Remove(data);});
    return allRemoved;
  }

  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& inputC) {
    bool someInserted = false;
    inputC.Traverse([&someInserted, this](const Data& data) {someInserted |= Insert(data);});
    return someInserted;
  }

  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& inputC) {
    bool someInserted = false;
    inputC.Map([&someInserted, this](Data& data) {someInserted |= Insert(std::move(data));});
    return someInserted;
  }

  template <typename Data>
  inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& inputC) {
    bool someRemoved = false;
    inputC.Traverse([&someRemoved, this](const Data& data) {someRemoved |= Remove(data);});
    return someRemoved;
  }
}