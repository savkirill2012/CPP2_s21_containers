// RBNode realization

template <typename K, typename T>
RBNode<K, T>::RBNode()  // default = nill
    : left(nullptr), rigth(nullptr), p(nullptr), loc_counter_(0), color_(-1) {}

template <typename K, typename T>
RBNode<K, T>::RBNode(K key, T value)
    : key_(key),
      value_(value),
      left(nullptr),
      rigth(nullptr),
      p(nullptr),
      loc_counter_(1),
      color_(0) {}

template <typename K, typename T>
RBNode<K, T>& RBNode<K, T>::operator=(const RBNode& other) {
  if (this == &other) return *this;

  key_ = other.key_;
  value_ = other.value_;
  left = other.left;
  rigth = other.rigth;
  p = other.p;
  color_ = other.color_;
  loc_counter_ = other.loc_counter_;

  return *this;
}

template <typename K, typename T>
RBNode<K, T>& RBNode<K, T>::operator=(RBNode&& other) {
  if (this == &other) return *this;

  key_ = other.key_;
  value_ = other.value_;
  left = other.left;
  rigth = other.rigth;
  p = other.p;
  color_ = other.color_;
  loc_counter_ = other.loc_counter_;

  return *this;
}

template <typename K, typename T>
K& RBNode<K, T>::GetKey() {
  return key_;
}

template <typename K, typename T>
const K& RBNode<K, T>::GetKey() const {
  return key_;
}

template <typename K, typename T>
T& RBNode<K, T>::GetValue() {
  return value_;
}

template <typename K, typename T>
const T& RBNode<K, T>::GetValue() const {
  return value_;
}

template <typename K, typename T>
RBNode<K, T>* RBNode<K, T>::GetLeftRef() const {
  return left;
}

template <typename K, typename T>
RBNode<K, T>* RBNode<K, T>::GetRigthRef() const {
  return rigth;
}

template <typename K, typename T>
RBNode<K, T>* RBNode<K, T>::GetParentRef() const {
  return p;
}

template <typename K, typename T>
int RBNode<K, T>::GetColor() const {
  return color_;
}

template <typename K, typename T>
int RBNode<K, T>::GetLocCounter() const {
  return loc_counter_;
}

template <typename K, typename T>
void RBNode<K, T>::SetVal(T val) {
  value_ = val;
}

template <typename K, typename T>
void RBNode<K, T>::SetKey(K key) {
  key_ = key;
}

template <typename K, typename T>
void RBNode<K, T>::SetLRef(RBNode* pointer) {
  left = pointer;
}

template <typename K, typename T>
void RBNode<K, T>::SetRRef(RBNode* pointer) {
  rigth = pointer;
}

template <typename K, typename T>
void RBNode<K, T>::SetPRef(RBNode* pointer) {
  p = pointer;
}

template <typename K, typename T>
void RBNode<K, T>::SetBlackClolr() {
  color_ = 1;
}

template <typename K, typename T>
void RBNode<K, T>::SetRedColor() {
  color_ = 0;
}

template <typename K, typename T>
void RBNode<K, T>::SetColor(int color) {
  color_ = color;
}

template <typename K, typename T>
void RBNode<K, T>::SetLocCounter(int new_loc_counter) {
  loc_counter_ = new_loc_counter;
}

template <typename K, typename T>
void RBNode<K, T>::IncLocCounter() {
  loc_counter_++;
}

// RBTree realization

template <typename K, typename T>
RBTree<K, T>::RBTree(K key, T value) : len_(0), len_m_(0) {
  nill_ = new RBNode<K, T>();
  try {
    root_ = new RBNode<K, T>(key, value);
  } catch (std::bad_alloc&) {
    delete nill_;
    throw;
  }
  root_->SetBlackClolr();
  root_->SetPRef(nill_);
  root_->SetLRef(nill_);
  root_->SetRRef(nill_);
  len_++;
  len_m_++;
}

template <typename K, typename T>
RBTree<K, T>::RBTree(const RBTree& tree)
    : nill_(new RBNode<K, T>()), len_(tree.len_), len_m_(tree.len_m_) {
  try {
    root_ = _copyNode(tree.root_, nill_);
  } catch (std::bad_alloc&) {
    delete nill_;
    throw;
  }

  try {
    _copyTree(tree.root_, root_);
  } catch (std::bad_alloc&) {
    _deleteRBTree(root_);
    delete nill_;
    throw;
  }
}

template <typename K, typename T>
RBTree<K, T>::RBTree(RBTree&& tree) : len_(tree.len_), len_m_(tree.len_m_) {
  std::swap(root_, tree.root_);
  std::swap(nill_, tree.nill_);
}

template <typename K, typename T>
RBNode<K, T>* RBTree<K, T>::_copyNode(RBNode<K, T>* node,
                                      RBNode<K, T>* parent_node) {
  if (node == nullptr) {
    return nullptr;
  }
  RBNode<K, T>* ret_node = new RBNode<K, T>(node->GetKey(), node->GetValue());
  ret_node->SetColor(node->GetColor());
  ret_node->SetLocCounter(node->GetLocCounter());
  ret_node->SetLRef(nill_);
  ret_node->SetRRef(nill_);
  ret_node->SetPRef(parent_node);
  return ret_node;
}

template <typename K, typename T>
void RBTree<K, T>::_copyTree(RBNode<K, T>* node, RBNode<K, T>* copy_node) {
  if (node != nullptr) {
    if (node->GetLeftRef()->GetColor() != -1) {
      copy_node->SetLRef(_copyNode(node->GetLeftRef(), copy_node));
      _copyTree(node->GetLeftRef(), copy_node->GetLeftRef());
    }

    if (node->GetRigthRef()->GetColor() != -1) {
      copy_node->SetRRef(_copyNode(node->GetRigthRef(), copy_node));
      _copyTree(node->GetRigthRef(), copy_node->GetRigthRef());
    }
  }
}

template <typename K, typename T>
RBTree<K, T>::RBTree() : root_(nullptr), len_(0), len_m_(0) {
  nill_ = new RBNode<K, T>();
}

template <typename K, typename T>
RBTree<K, T>::~RBTree() {
  if (len_ != 0) {
    _deleteRBTree(root_);
  }

  delete nill_;
}

template <typename K, typename T>
RBTree<K, T>& RBTree<K, T>::operator=(const RBTree<K, T>& tree) {
  if (this == &tree) return *this;

  if (root_ != nullptr) {
    _deleteRBTree(root_);
  }

  if (nill_ != nullptr) {
    delete nill_;
  }
  nill_ = new RBNode<K, T>();
  root_ = _copyNode(tree.root_, nill_);
  _copyTree(tree.root_, root_);
  len_ = tree.len_;
  len_m_ = tree.len_m_;

  return *this;
}

template <typename K, typename T>
T& RBTree<K, T>::operator[](const K& key) {
  return GetNode(key)->GetValue();
}

template <typename K, typename T>
typename RBTree<K, T>::iterator_map RBTree<K, T>::begin() {
  if (root_ == nullptr) {
    return _RBTree_iterator_multiset<K, T>(nill_);
  }

  RBNode<K, T>* curent_node = root_;
  while (curent_node->GetLeftRef()->GetColor() != -1) {
    curent_node = curent_node->GetLeftRef();
  }

  return _RBTree_iterator_map<K, T>(curent_node);
}

template <typename K, typename T>
typename RBTree<K, T>::iterator_multiset RBTree<K, T>::begin_m() const {
  if (root_ == nullptr) {
    return _RBTree_iterator_multiset<K, T>(nill_);
  }

  RBNode<K, T>* curent_node = root_;
  while (curent_node->GetLeftRef()->GetColor() != -1) {
    curent_node = curent_node->GetLeftRef();
  }

  return _RBTree_iterator_multiset<K, T>(curent_node);
  // return begin();
}

template <typename K, typename T>
typename RBTree<K, T>::iterator_map RBTree<K, T>::end() {
  if (root_ == nullptr) {
    return _RBTree_iterator_multiset<K, T>(nill_);
  }

  RBNode<K, T>* prev_node = root_;
  while (prev_node->GetRigthRef()->GetColor() != -1) {
    prev_node = prev_node->GetRigthRef();
  }

  return _RBTree_iterator_map<K, T>(nill_, prev_node);
}

template <typename K, typename T>
typename RBTree<K, T>::iterator_multiset RBTree<K, T>::end_m() const {
  if (root_ == nullptr) {
    return _RBTree_iterator_multiset<K, T>(nill_);
  }

  RBNode<K, T>* prev_node = root_;
  while (prev_node->GetRigthRef()->GetColor() != -1) {
    prev_node = prev_node->GetRigthRef();
  }

  return _RBTree_iterator_multiset<K, T>(nill_, prev_node);
}

template <typename K, typename T>
std::size_t RBTree<K, T>::len() {
  return len_;
}

template <typename K, typename T>
std::size_t RBTree<K, T>::len_m() {
  return len_m_;
}

template <typename K, typename T>
void RBTree<K, T>::add(K key, T value) {
  if (root_ == nullptr) {
    root_ = new RBNode<K, T>(key, value);
    root_->SetBlackClolr();
    root_->SetPRef(nill_);
    root_->SetLRef(nill_);
    root_->SetRRef(nill_);
    len_++;
    len_m_++;
  } else {
    RBNode<K, T>* add_node = new RBNode<K, T>(key, value);
    RBNode<K, T>* current_node = root_;

    while (1) {
      if (add_node->GetKey() > current_node->GetKey()) {
        // rigth
        if (current_node->GetRigthRef()->GetColor() == -1) {
          current_node->SetRRef(add_node);
          add_node->SetPRef(current_node);
          add_node->SetLRef(nill_);
          add_node->SetRRef(nill_);
          current_node = current_node->GetRigthRef();
          break;
        } else {
          current_node = current_node->GetRigthRef();
        }
      } else if (add_node->GetKey() < current_node->GetKey()) {
        // left
        if (current_node->GetLeftRef()->GetColor() == -1) {
          current_node->SetLRef(add_node);
          add_node->SetPRef(current_node);
          add_node->SetLRef(nill_);
          add_node->SetRRef(nill_);
          current_node = current_node->GetLeftRef();
          break;
        } else {
          current_node = current_node->GetLeftRef();
        }
      } else {
        // replace
        current_node->SetVal(value);
        current_node->IncLocCounter();
        delete add_node;
        len_--;
        break;
      }
    }

    _balanser(current_node);
    len_++;
    len_m_++;
  }
}

template <typename K, typename T>
void RBTree<K, T>::_balanser(RBNode<K, T>* curent_node) {
  RBNode<K, T>* up_node = curent_node->GetParentRef();
  RBNode<K, T>* loc_node = curent_node;

  while (up_node != nill_) {
    if (loc_node->GetColor() == 0 && up_node->GetColor() == 0) {
      RBNode<K, T>* parent_node = up_node->GetParentRef();
      if ((parent_node->GetLeftRef() == up_node &&
           up_node->GetRigthRef() == loc_node) ||
          (parent_node->GetRigthRef() == up_node &&
           up_node->GetLeftRef() == loc_node)) {
        // turn loc
        _turnLoc(loc_node, up_node);
        up_node = loc_node;
      }

      RBNode<K, T>* uncle_node = _uncleSearch(up_node);

      if (uncle_node->GetColor() == 0) {
        // swap colors
        _swapColors(up_node, uncle_node);
      } else if (uncle_node->GetColor() == 1 || uncle_node->GetColor() == -1) {
        // turn
        _turn(up_node, parent_node);
        up_node->SetBlackClolr();
        parent_node->SetRedColor();
      }
    }
    loc_node = up_node;
    up_node = loc_node->GetParentRef();
  }

  root_->SetBlackClolr();  // перекраска рута в теории
}

template <typename K, typename T>
void RBTree<K, T>::_turnLoc(RBNode<K, T>* curent_node, RBNode<K, T>* up_node) {
  if (up_node->GetParentRef()->GetLeftRef() == up_node) {
    up_node->GetParentRef()->SetLRef(curent_node);
  } else {
    up_node->GetParentRef()->SetRRef(curent_node);
  }
  curent_node->SetPRef(up_node->GetParentRef());
  up_node->SetPRef(curent_node);
  if (up_node->GetRigthRef() == curent_node) {  // left
    up_node->SetRRef(curent_node->GetLeftRef());
    curent_node->GetLeftRef()->SetPRef(up_node);
    curent_node->SetLRef(up_node);
  } else if (up_node->GetLeftRef() == curent_node) {  // rigth
    up_node->SetLRef(curent_node->GetRigthRef());
    curent_node->GetRigthRef()->SetPRef(up_node);
    curent_node->SetRRef(up_node);
  }
}

template <typename K, typename T>
void RBTree<K, T>::_swapColors(RBNode<K, T>* up_node,
                               RBNode<K, T>* uncle_node) {
  up_node->SetBlackClolr();
  up_node->GetParentRef()->SetRedColor();
  uncle_node->SetBlackClolr();
}

template <typename K, typename T>
void RBTree<K, T>::_turn(RBNode<K, T>* up_node, RBNode<K, T>* parent_node) {
  RBNode<K, T>* grandparent_node = nullptr;

  if (parent_node->GetParentRef() != nill_) {
    grandparent_node = parent_node->GetParentRef();
  }

  if (grandparent_node != nullptr) {
    if (grandparent_node->GetLeftRef() == parent_node) {
      grandparent_node->SetLRef(up_node);
    } else {
      grandparent_node->SetRRef(up_node);
    }
    up_node->SetPRef(grandparent_node);
  } else {
    up_node->SetPRef(nill_);
    root_ = up_node;
  }

  parent_node->SetPRef(up_node);

  if (parent_node->GetLeftRef() == up_node) {
    parent_node->SetLRef(up_node->GetRigthRef());
    up_node->GetRigthRef()->SetPRef(parent_node);
    up_node->SetRRef(parent_node);
  } else {
    parent_node->SetRRef(up_node->GetLeftRef());
    up_node->GetLeftRef()->SetPRef(parent_node);
    up_node->SetLRef(parent_node);
  }
}

template <typename K, typename T>
void RBTree<K, T>::remove(K key) {
  if (root_ != nullptr && root_->GetColor() != -1) {
    RBNode<K, T>* cur_node = root_;

    while (cur_node->GetColor() != -1 && key != cur_node->GetKey()) {
      if (cur_node->GetKey() > key) {
        cur_node = cur_node->GetLeftRef();
      } else {
        cur_node = cur_node->GetRigthRef();
      }
    }

    if (cur_node->GetColor() != -1) {
      len_m_ -= (std::size_t)cur_node->GetLocCounter();
      if (cur_node->GetColor() == 0) {
        if (cur_node->GetRigthRef() == nill_) {
          // 1 del red node with 0 child -> just del with replace to nill
          _delRedNZeroChild(cur_node);
        } else {
          // 2 del any color node with 2 child
          // |-> swap key and value with next left or next rigth val (color
          // don't change) after delete
          _delNodeTwoCild(cur_node);
        }
      } else {
        if (cur_node->GetLeftRef() != nill_ &&
            cur_node->GetRigthRef() != nill_) {
          // 2 del any color node with 2 child
          // |-> swap key and value with next left or next rigth val (color
          // don't change) after delete
          _delNodeTwoCild(cur_node);
        } else if (cur_node->GetLeftRef() == nill_ &&
                   cur_node->GetRigthRef() == nill_) {
          // 4 del black node with 0 child and rebalanse after all
          //                                   |-> need to realize rebalanser
          _rebalanser(cur_node);
          _delBlackNZeroChild(cur_node);
        } else {
          // 3 del black node with 1 child swap values (without color change)
          // with child
          _delBlackNOneChild(cur_node);
        }
      }
      len_--;
    }
  }
}

template <typename K, typename T>
void RBTree<K, T>::remove_m(K key) {
  RBNode<K, T>* rm_node = GetNode(key);
  if (rm_node->GetColor() != -1) {
    if (rm_node->GetLocCounter() != 1) {
      rm_node->SetLocCounter(rm_node->GetLocCounter() - 1);
      len_m_--;
    } else {
      remove(key);
    }
  }
}

template <typename K, typename T>
void RBTree<K, T>::_delRedNZeroChild(RBNode<K, T>* del_node) {
  RBNode<K, T>* parent_node = del_node->GetParentRef();
  if (parent_node->GetLeftRef() == del_node) {
    parent_node->SetLRef(nill_);
  } else {
    parent_node->SetRRef(nill_);
  }
  delete del_node;
}

template <typename K, typename T>
void RBTree<K, T>::_delNodeTwoCild(RBNode<K, T>* del_node) {
  RBNode<K, T>* swap_node = del_node->GetLeftRef();

  while (swap_node->GetRigthRef() != nill_) {
    swap_node = swap_node->GetRigthRef();
  }

  del_node->SetKey(swap_node->GetKey());
  del_node->SetVal(swap_node->GetValue());
  del_node->SetLocCounter(swap_node->GetLocCounter());

  if (swap_node->GetColor() == 0) {
    _delRedNZeroChild(swap_node);
  } else {
    if (swap_node->GetLeftRef() == nill_) {
      _rebalanser(swap_node);
      _delBlackNZeroChild(swap_node);
    } else {
      _delBlackNOneChild(swap_node);
    }
  }
}

template <typename K, typename T>
void RBTree<K, T>::_delBlackNOneChild(RBNode<K, T>* del_node) {
  RBNode<K, T>* swap_node = nullptr;

  if (del_node->GetLeftRef() == nill_) {
    swap_node = del_node->GetRigthRef();
  } else {
    swap_node = del_node->GetLeftRef();
  }

  del_node->SetKey(swap_node->GetKey());
  del_node->SetVal(swap_node->GetValue());
  del_node->SetLocCounter(swap_node->GetLocCounter());

  _delRedNZeroChild(swap_node);  // check is always so
}

template <typename K, typename T>
bool RBTree<K, T>::_rebalanser(RBNode<K, T>* del_node) {
  RBNode<K, T>* parent_node = del_node->GetParentRef();
  if (parent_node == nill_) {
    return 1;
  }

  RBNode<K, T>* uncle_node = _uncleSearch(del_node);

  if (uncle_node != nill_) {
    RBNode<K, T>* siblin_out_node = _siblinOutSearch(del_node, parent_node);
    RBNode<K, T>* siblin_in_node = _siblinInSearch(del_node, parent_node);

    if (uncle_node->GetColor() == 1 && siblin_in_node->GetColor() == 0 &&
        (siblin_out_node->GetColor() == 1 ||
         siblin_out_node->GetColor() == -1)) {
      _turnLoc(siblin_in_node, uncle_node);
      siblin_in_node->SetBlackClolr();
      uncle_node->SetRedColor();
      siblin_out_node = uncle_node;
      uncle_node = siblin_in_node;
    }

    if (uncle_node->GetColor() == 1 && siblin_out_node->GetColor() == 0) {
      _turn(uncle_node, parent_node);
      uncle_node->SetColor(parent_node->GetColor());
      parent_node->SetBlackClolr();
      siblin_out_node->SetBlackClolr();
      // end
      return 1;
    } else if (uncle_node->GetColor() == 1) {
      uncle_node->SetRedColor();
      if (parent_node->GetColor() == 0) {
        parent_node->SetBlackClolr();
        // end
        return 1;
      } else if (parent_node->GetColor() == 1) {
        // recursiv
        return _rebalanser(parent_node);
      }
    } else if (uncle_node->GetColor() == 0) {
      _turn(uncle_node, parent_node);
      uncle_node->SetBlackClolr();
      parent_node->SetRedColor();
      // recursiv
      return _rebalanser(del_node);
    }
  }

  return 1;
}

template <typename K, typename T>
void RBTree<K, T>::_delBlackNZeroChild(RBNode<K, T>* del_node) {
  RBNode<K, T>* parent_node = del_node->GetParentRef();
  if (parent_node->GetLeftRef() == del_node) {
    parent_node->SetLRef(nill_);
  } else {
    parent_node->SetRRef(nill_);
  }

  delete del_node;
}

template <typename K, typename T>
RBNode<K, T>* RBTree<K, T>::_uncleSearch(RBNode<K, T>* curent_node) {
  RBNode<K, T>* parent_node = curent_node->GetParentRef();
  if (parent_node->GetLeftRef() == curent_node) {
    return parent_node->GetRigthRef();
  } else if (parent_node->GetRigthRef() == curent_node) {
    return parent_node->GetLeftRef();
  } else {
    return nullptr;
  }
}

template <typename K, typename T>
RBNode<K, T>* RBTree<K, T>::_siblinOutSearch(RBNode<K, T>* curent_node,
                                             RBNode<K, T>* parent_node) {
  if (parent_node->GetLeftRef() == curent_node) {
    return parent_node->GetRigthRef()->GetRigthRef();
  } else if (parent_node->GetRigthRef() == curent_node) {
    return parent_node->GetLeftRef()->GetLeftRef();
  } else {
    return nullptr;
  }
}

template <typename K, typename T>
RBNode<K, T>* RBTree<K, T>::_siblinInSearch(RBNode<K, T>* curent_node,
                                            RBNode<K, T>* parent_node) {
  if (parent_node->GetLeftRef() == curent_node) {
    return parent_node->GetRigthRef()->GetLeftRef();
  } else if (parent_node->GetRigthRef() == curent_node) {
    return parent_node->GetLeftRef()->GetRigthRef();
  } else {
    return nullptr;
  }
}

template <typename K, typename T>
void RBTree<K, T>::_deleteRBTree(RBNode<K, T>* del_node) {
  if (del_node->GetLeftRef() != nullptr &&
      del_node->GetLeftRef()->GetColor() != -1) {
    _deleteRBTree(del_node->GetLeftRef());
  }

  if (del_node->GetRigthRef() != nullptr &&
      del_node->GetRigthRef()->GetColor() != -1) {
    _deleteRBTree(del_node->GetRigthRef());
  }

  delete del_node;
}

template <typename K, typename T>
void RBTree<K, T>::clear() {
  if (len_ != 0) {
    _deleteRBTree(root_);
    len_ = 0;
    len_m_ = 0;
  }
  root_ = nullptr;
}

template <typename K, typename T>
bool RBTree<K, T>::empty() const {
  if (len_ == 0) {
    return true;
  } else {
    return false;
  }
}

template <typename K, typename T>
RBNode<K, T>* RBTree<K, T>::GetNode(K key) const {
  if (root_ == nullptr) {
    return nill_;
  }

  RBNode<K, T>* cur_node = root_;
  while (cur_node->GetColor() != -1 && key != cur_node->GetKey()) {
    if (cur_node->GetKey() > key) {
      cur_node = cur_node->GetLeftRef();
    } else {
      cur_node = cur_node->GetRigthRef();
    }
  }

  return cur_node;
}

template <typename K, typename T>
RBNode<K, T>* RBTree<K, T>::SearchPrevNode(RBNode<K, T>* node) const {
  K key = node->GetKey();
  RBNode<K, T>* cur_node = root_;
  K nearest_key = cur_node->GetKey();

  while (key != cur_node->GetKey()) {
    if (nearest_key < cur_node->GetKey() && cur_node->GetKey() < key) {
      nearest_key = cur_node->GetKey();
    }

    if (key > cur_node->GetKey()) {
      cur_node = cur_node->GetRigthRef();
    } else if (key < cur_node->GetKey()) {
      cur_node = cur_node->GetLeftRef();
    }
  }

  return GetNode(key);
}

template <typename K, typename T>
std::size_t RBTree<K, T>::GetSizeM() const {
  return len_m_;
}

// _RBTree_iterator_map realization

template <typename K, typename T>
_RBTree_iterator_map<K, T>::_RBTree_iterator_map()
    : pointer_(nullptr), prev_pointer_(nullptr) {}

template <typename K, typename T>
_RBTree_iterator_map<K, T>::_RBTree_iterator_map(
    const _RBTree_iterator_map<K, T>& other)
    : pointer_(other.pointer_), prev_pointer_(other.prev_pointer_) {}

template <typename K, typename T>
_RBTree_iterator_map<K, T>::_RBTree_iterator_map(
    _RBTree_iterator_map<K, T>&& other)
    : pointer_(other.pointer_), prev_pointer_(other.prev_pointer_) {}

template <typename K, typename T>
_RBTree_iterator_map<K, T>::_RBTree_iterator_map(RBNode<K, T>* node)
    : pointer_(node), prev_pointer_(nullptr) {}

template <typename K, typename T>
_RBTree_iterator_map<K, T>::_RBTree_iterator_map(RBNode<K, T>* node,
                                                 RBNode<K, T>* prev_node)
    : pointer_(node), prev_pointer_(prev_node) {}

template <typename K, typename T>
_RBTree_iterator_map<K, T>& _RBTree_iterator_map<K, T>::operator=(
    const _RBTree_iterator_map& node) {
  if (this == &node) return *this;

  pointer_ = node.pointer_;
  prev_pointer_ = node.prev_pointer_;

  return *this;
}

template <typename K, typename T>
_RBTree_iterator_map<K, T>& _RBTree_iterator_map<K, T>::operator=(
    _RBTree_iterator_map&& node) {
  if (this == &node) return *this;
  pointer_ = node.pointer_;
  prev_pointer_ = node.prev_pointer_;

  return *this;
}

template <typename K, typename T>
T& _RBTree_iterator_map<K, T>::operator*() {
  return pointer_->GetValue();
}

template <typename K, typename T>
const T& _RBTree_iterator_map<K, T>::operator*() const {
  return pointer_->GetValue();
}

template <typename K, typename T>
_RBTree_iterator_map<K, T>& _RBTree_iterator_map<K, T>::operator++() {
  if (pointer_->GetColor() == -1) {
    return *this;
  }

  prev_pointer_ = pointer_;
  RBNode<K, T>* cur_node = pointer_;
  while (cur_node->GetRigthRef()->GetColor() != -1) {
    cur_node = cur_node->GetRigthRef();
  }

  if (cur_node == pointer_) {
    while (pointer_->GetParentRef()->GetRigthRef() == pointer_) {
      pointer_ = pointer_->GetParentRef();
    }
    pointer_ = pointer_->GetParentRef();
  } else {
    pointer_ = pointer_->GetRigthRef();
    while (pointer_->GetLeftRef()->GetColor() != -1) {
      pointer_ = pointer_->GetLeftRef();
    }
  }

  return *this;
}

template <typename K, typename T>
const _RBTree_iterator_map<K, T>& _RBTree_iterator_map<K, T>::operator++()
    const {
  if (pointer_->GetColor() == -1) {
    return *this;
  }

  prev_pointer_ = pointer_;
  RBNode<K, T>* cur_node = pointer_;
  while (cur_node->GetRigthRef()->GetColor() != -1) {
    cur_node = cur_node->GetRigthRef();
  }

  if (cur_node == pointer_) {
    while (pointer_->GetParentRef()->GetRigthRef() == pointer_) {
      pointer_ = pointer_->GetParentRef();
    }
    pointer_ = pointer_->GetParentRef();
  } else {
    pointer_ = pointer_->GetRigthRef();
    while (pointer_->GetLeftRef()->GetColor() != -1) {
      pointer_ = pointer_->GetLeftRef();
    }
  }

  return *this;
}

template <typename K, typename T>
_RBTree_iterator_map<K, T> _RBTree_iterator_map<K, T>::operator++(int) const {
  _RBTree_iterator_map<K, T> tmp = *this;
  ++(*this);
  return tmp;
}

template <typename K, typename T>
_RBTree_iterator_map<K, T>& _RBTree_iterator_map<K, T>::operator--() {
  if (prev_pointer_->GetColor() == -1) {
    return *this;
  }

  pointer_ = prev_pointer_;
  RBNode<K, T>* cur_node = prev_pointer_;
  while (cur_node->GetLeftRef()->GetColor() != -1) {
    cur_node = cur_node->GetLeftRef();
  }

  if (cur_node == prev_pointer_) {
    while (prev_pointer_->GetParentRef()->GetLeftRef() == prev_pointer_) {
      prev_pointer_ = prev_pointer_->GetParentRef();
    }
    prev_pointer_ = prev_pointer_->GetParentRef();
  } else {
    prev_pointer_ = prev_pointer_->GetLeftRef();
    while (prev_pointer_->GetRigthRef()->GetColor() != -1) {
      prev_pointer_ = prev_pointer_->GetRigthRef();
    }
  }

  return *this;
}

template <typename K, typename T>
const _RBTree_iterator_map<K, T>& _RBTree_iterator_map<K, T>::operator--()
    const {
  if (prev_pointer_->GetColor() == -1) {
    return *this;
  }

  pointer_ = prev_pointer_;
  RBNode<K, T>* cur_node = prev_pointer_;
  while (cur_node->GetLeftRef()->GetColor() != -1) {
    cur_node = cur_node->GetLeftRef();
  }

  if (cur_node == prev_pointer_) {
    while (prev_pointer_->GetParentRef()->GetLeftRef() == prev_pointer_) {
      prev_pointer_ = prev_pointer_->GetParentRef();
    }
    prev_pointer_ = prev_pointer_->GetParentRef();
  } else {
    prev_pointer_ = prev_pointer_->GetLeftRef();
    while (prev_pointer_->GetRigthRef()->GetColor() != -1) {
      prev_pointer_ = prev_pointer_->GetRigthRef();
    }
  }

  return *this;
}

template <typename K, typename T>
_RBTree_iterator_map<K, T> _RBTree_iterator_map<K, T>::operator--(int) const {
  _RBTree_iterator_map<K, T> tmp = *this;
  --(*this);
  return tmp;
}

template <typename K, typename T>
RBNode<K, T>* _RBTree_iterator_map<K, T>::GetPointer() const {
  return pointer_;
}

template <typename K, typename T>
RBNode<K, T>* _RBTree_iterator_map<K, T>::GetPrevPointer() const {
  return prev_pointer_;
}

template <typename K, typename T>
void _RBTree_iterator_map<K, T>::SetPointer(RBNode<K, T>* node) const {
  pointer_ = node;
}

template <typename K, typename T>
void _RBTree_iterator_map<K, T>::SetPrevPointer(RBNode<K, T>* node) const {
  prev_pointer_ = node;
}

template <typename K, typename T>
bool _RBTree_iterator_map<K, T>::operator==(
    const _RBTree_iterator_map& other) const {
  if (pointer_ == other.pointer_) {
    return true;
  } else {
    return false;
  }
}

template <typename K, typename T>
bool _RBTree_iterator_map<K, T>::operator!=(
    const _RBTree_iterator_map& other) const {
  if (pointer_ == other.pointer_) {
    return false;
  } else {
    return true;
  }
}

// _RBTree_iterator_multiset realization

template <typename K, typename T>
_RBTree_iterator_multiset<K, T>& _RBTree_iterator_multiset<K, T>::operator=(
    const _RBTree_iterator_multiset& other) {
  if (this == &other) return *this;

  RBNode<K, T>* pointer = this->GetPointer();
  RBNode<K, T>* prev_pointer = this->GetPrevPointer();
  pointer = static_cast<_RBTree_iterator_map<K, T>>(other).GetPointer();
  prev_pointer =
      static_cast<_RBTree_iterator_map<K, T>>(other).GetPrevPointer();
  this->SetPointer(pointer);
  this->SetPrevPointer(prev_pointer);
  count_in_node_ = other.count_in_node_;

  return *this;
}

template <typename K, typename T>
_RBTree_iterator_multiset<K, T>& _RBTree_iterator_multiset<K, T>::operator=(
    _RBTree_iterator_multiset&& other) {
  if (this == &other) return *this;

  *this = other;

  return *this;
}

template <typename K, typename T>
_RBTree_iterator_map<K, T>& _RBTree_iterator_multiset<K, T>::operator++() {
  RBNode<K, T>* pointer_ = this->GetPointer();
  if (pointer_->GetColor() == -1) {
    return *this;
  }
  this->SetPrevPointer(pointer_);
  count_in_node_++;

  if (count_in_node_ != pointer_->GetLocCounter()) {
    return *this;
  }

  RBNode<K, T>* cur_node = pointer_;
  while (cur_node->GetRigthRef()->GetColor() != -1) {
    cur_node = cur_node->GetRigthRef();
  }

  if (cur_node == pointer_) {
    while (pointer_->GetParentRef()->GetRigthRef() == pointer_) {
      pointer_ = pointer_->GetParentRef();
    }
    pointer_ = pointer_->GetParentRef();
  } else {
    pointer_ = pointer_->GetRigthRef();
    while (pointer_->GetLeftRef()->GetColor() != -1) {
      pointer_ = pointer_->GetLeftRef();
    }
  }

  this->SetPointer(pointer_);

  count_in_node_ = 0;

  return *this;
}

template <typename K, typename T>
const _RBTree_iterator_map<K, T>& _RBTree_iterator_multiset<K, T>::operator++()
    const {
  RBNode<K, T>* pointer_ = this->GetPointer();
  if (pointer_->GetColor() == -1) {
    return *this;
  }
  this->SetPrevPointer(pointer_);
  count_in_node_++;

  if (count_in_node_ != pointer_->GetLocCounter()) {
    return *this;
  }

  RBNode<K, T>* cur_node = pointer_;
  while (cur_node->GetRigthRef()->GetColor() != -1) {
    cur_node = cur_node->GetRigthRef();
  }

  if (cur_node == pointer_) {
    while (pointer_->GetParentRef()->GetRigthRef() == pointer_) {
      pointer_ = pointer_->GetParentRef();
    }
    pointer_ = pointer_->GetParentRef();
  } else {
    pointer_ = pointer_->GetRigthRef();
    while (pointer_->GetLeftRef()->GetColor() != -1) {
      pointer_ = pointer_->GetLeftRef();
    }
  }

  this->SetPointer(pointer_);

  count_in_node_ = 0;

  return *this;
}

template <typename K, typename T>
_RBTree_iterator_map<K, T> _RBTree_iterator_multiset<K, T>::operator++(
    int) const {
  _RBTree_iterator_multiset<K, T> tmp = *this;
  ++(*this);
  return std::move(tmp);
}

template <typename K, typename T>
_RBTree_iterator_map<K, T>& _RBTree_iterator_multiset<K, T>::operator--() {
  RBNode<K, T>* prev_pointer_ = this->GetPrevPointer();
  if (prev_pointer_->GetColor() == -1) {
    return *this;
  }
  this->SetPointer(prev_pointer_);
  count_in_node_++;

  if (count_in_node_ != prev_pointer_->GetLocCounter()) {
    return *this;
  }

  RBNode<K, T>* cur_node = prev_pointer_;
  while (cur_node->GetLeftRef()->GetColor() != -1) {
    cur_node = cur_node->GetLeftRef();
  }

  if (cur_node == prev_pointer_) {
    while (prev_pointer_->GetParentRef()->GetLeftRef() == prev_pointer_) {
      prev_pointer_ = prev_pointer_->GetParentRef();
    }
    prev_pointer_ = prev_pointer_->GetParentRef();
  } else {
    prev_pointer_ = prev_pointer_->GetLeftRef();
    while (prev_pointer_->GetRigthRef()->GetColor() != -1) {
      prev_pointer_ = prev_pointer_->GetRigthRef();
    }
  }

  this->SetPrevPointer(prev_pointer_);

  count_in_node_ = 0;

  return *this;
}

template <typename K, typename T>
const _RBTree_iterator_map<K, T>& _RBTree_iterator_multiset<K, T>::operator--()
    const {
  RBNode<K, T>* prev_pointer_ = this->GetPrevPointer();
  if (prev_pointer_->GetColor() == -1) {
    return *this;
  }
  this->SetPointer(prev_pointer_);
  count_in_node_++;

  if (count_in_node_ != prev_pointer_->GetLocCounter()) {
    return *this;
  }

  RBNode<K, T>* cur_node = prev_pointer_;
  while (cur_node->GetLeftRef()->GetColor() != -1) {
    cur_node = cur_node->GetLeftRef();
  }

  if (cur_node == prev_pointer_) {
    while (prev_pointer_->GetParentRef()->GetLeftRef() == prev_pointer_) {
      prev_pointer_ = prev_pointer_->GetParentRef();
    }
    prev_pointer_ = prev_pointer_->GetParentRef();
  } else {
    prev_pointer_ = prev_pointer_->GetLeftRef();
    while (prev_pointer_->GetRigthRef()->GetColor() != -1) {
      prev_pointer_ = prev_pointer_->GetRigthRef();
    }
  }

  this->SetPrevPointer(prev_pointer_);

  count_in_node_ = 0;

  return *this;
}

template <typename K, typename T>
_RBTree_iterator_map<K, T> _RBTree_iterator_multiset<K, T>::operator--(
    int) const {
  _RBTree_iterator_map<K, T> tmp = *this;
  --(*this);
  return tmp;
}
