#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>

template <typename K, typename T>
class RBNode final {
 public:
  RBNode();
  RBNode(K key, T value);

  RBNode<K, T>& operator=(const RBNode& other);
  RBNode<K, T>& operator=(RBNode&& other);

  K& GetKey();
  const K& GetKey() const;
  T& GetValue();
  const T& GetValue() const;
  RBNode<K, T>* GetLeftRef() const;
  RBNode<K, T>* GetRigthRef() const;
  RBNode<K, T>* GetParentRef() const;
  int GetColor() const;
  int GetLocCounter() const;

  void SetVal(T val);
  void SetKey(K key);
  void SetLRef(RBNode* pointer);
  void SetRRef(RBNode* pointer);
  void SetPRef(RBNode* pointer);
  void SetBlackClolr();
  void SetRedColor();
  void SetColor(int color);
  void SetLocCounter(int new_loc_counter);
  void IncLocCounter();

 private:
  K key_;
  T value_;
  RBNode<K, T>* left;
  RBNode<K, T>* rigth;
  RBNode<K, T>* p;
  int loc_counter_;
  int color_;
};

template <typename K, typename T>
class _RBTree_iterator_map {
 public:
  _RBTree_iterator_map();
  _RBTree_iterator_map(const _RBTree_iterator_map<K, T>& other);
  _RBTree_iterator_map(_RBTree_iterator_map<K, T>&& other);
  _RBTree_iterator_map(RBNode<K, T>* node);
  _RBTree_iterator_map(RBNode<K, T>* node, RBNode<K, T>* prev_node);

  _RBTree_iterator_map& operator=(const _RBTree_iterator_map& node);
  _RBTree_iterator_map& operator=(_RBTree_iterator_map&& node);
  T& operator*();
  const T& operator*() const;
  virtual _RBTree_iterator_map<K, T>& operator++();
  virtual const _RBTree_iterator_map<K, T>& operator++() const;
  virtual _RBTree_iterator_map<K, T> operator++(int) const;
  virtual _RBTree_iterator_map<K, T>& operator--();
  virtual const _RBTree_iterator_map<K, T>& operator--() const;
  virtual _RBTree_iterator_map<K, T> operator--(int) const;

  RBNode<K, T>* GetPointer() const;
  RBNode<K, T>* GetPrevPointer() const;

  void SetPointer(RBNode<K, T>* node) const;
  void SetPrevPointer(RBNode<K, T>* node) const;

  bool operator==(const _RBTree_iterator_map& other) const;
  bool operator!=(const _RBTree_iterator_map& other) const;

 private:
  mutable RBNode<K, T>* pointer_;
  mutable RBNode<K, T>* prev_pointer_;
};

template <typename K, typename T>
class _RBTree_iterator_multiset
    : public _RBTree_iterator_map<K, T> {  // maybe need to rewrigth
 public:
  _RBTree_iterator_multiset()
      : _RBTree_iterator_map<K, T>{}, count_in_node_(0){};
  _RBTree_iterator_multiset(const _RBTree_iterator_multiset<K, T>& other)
      : _RBTree_iterator_map<K, T>{other}, count_in_node_(0){};
  _RBTree_iterator_multiset(_RBTree_iterator_multiset<K, T>&& other)
      : _RBTree_iterator_map<K, T>{other}, count_in_node_(0){};
  _RBTree_iterator_multiset(RBNode<K, T>* node)
      : _RBTree_iterator_map<K, T>{node}, count_in_node_(0){};
  _RBTree_iterator_multiset(RBNode<K, T>* node, RBNode<K, T>* prev_node)
      : _RBTree_iterator_map<K, T>{node, prev_node}, count_in_node_(0){};

  _RBTree_iterator_multiset& operator=(const _RBTree_iterator_multiset& other);
  _RBTree_iterator_multiset& operator=(_RBTree_iterator_multiset&& other);

  _RBTree_iterator_map<K, T>& operator++() override;
  const _RBTree_iterator_map<K, T>& operator++() const override;
  _RBTree_iterator_map<K, T> operator++(int) const override;
  _RBTree_iterator_map<K, T>& operator--() override;
  const _RBTree_iterator_map<K, T>& operator--() const override;
  _RBTree_iterator_map<K, T> operator--(int) const override;

 private:
  mutable int count_in_node_;
};

template <typename K, typename T>
class RBTree final {
 public:
  using iterator_map = _RBTree_iterator_map<K, T>;
  using iterator_multiset = _RBTree_iterator_multiset<K, T>;

  RBTree();
  RBTree(const RBTree& tree);
  RBTree(RBTree&& tree);
  RBTree(K key, T value);
  ~RBTree();

  RBTree<K, T>& operator=(const RBTree<K, T>& tree);  // перегрузка для конст
  T& operator[](const K& key);  // перегрузка для конст

  iterator_multiset begin_m() const;
  iterator_multiset end_m() const;
  iterator_map begin();
  iterator_map end();
  std::size_t len();
  std::size_t len_m();
  void add(K key, T value);
  void remove(K key);
  void remove_m(K key);
  void clear();
  bool empty() const;
  RBNode<K, T>* GetNode(K key) const;
  RBNode<K, T>* SearchPrevNode(RBNode<K, T>* node) const;
  std::size_t GetSizeM() const;

 private:
  RBNode<K, T>* nill_;  // заглушка
  RBNode<K, T>* root_;  // корень
  std::size_t len_;
  std::size_t len_m_;

  void _balanser(RBNode<K, T>* curent_node);
  void _turnLoc(RBNode<K, T>* curent_node, RBNode<K, T>* up_node);
  void _swapColors(RBNode<K, T>* up_node, RBNode<K, T>* uncle_node);
  void _turn(RBNode<K, T>* up_node, RBNode<K, T>* parent_node);
  void _delRedNZeroChild(RBNode<K, T>* del_node);
  void _delNodeTwoCild(RBNode<K, T>* del_node);
  void _delBlackNOneChild(RBNode<K, T>* del_node);
  bool _rebalanser(RBNode<K, T>* del_node);
  void _delBlackNZeroChild(RBNode<K, T>* del_node);
  RBNode<K, T>* _uncleSearch(RBNode<K, T>* curent_node);
  RBNode<K, T>* _siblinOutSearch(RBNode<K, T>* curent_node,
                                 RBNode<K, T>* parent_node);
  RBNode<K, T>* _siblinInSearch(RBNode<K, T>* curent_node,
                                RBNode<K, T>* parent_node);
  void _deleteRBTree(RBNode<K, T>* del_node);
  RBNode<K, T>* _copyNode(RBNode<K, T>* node, RBNode<K, T>* parent_node);
  void _copyTree(RBNode<K, T>* node, RBNode<K, T>* copy_node);
};

#include "s21_rb.tpp"

#endif
