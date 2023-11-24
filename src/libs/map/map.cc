#include "map.h"

namespace s21 {
template <class Key, class Value>
map<Key, Value>::map() = default;

template <class Key, class Value>
map<Key, Value>::map(const map<Key, Value> &other) {
  for (auto itr = other.begin(); itr != other.end(); ++itr) {
    insert(*itr);
  }
}

template <class Key, class Value>
map<Key, Value>::map(map &&other) noexcept {
  root_ = nullptr;
  begin_node_ = nullptr;
  end_node_ = nullptr;
  size_ = 0;
  std::swap(root_, other.root_);
  std::swap(begin_node_, other.begin_node_);
  std::swap(end_node_, other.end_node_);
  std::swap(size_, other.size_);
}

template <class Key, class Value>
map<Key, Value> &map<Key, Value>::operator=(map &&other) noexcept {
  if (*this != other) {
    root_ = nullptr;
    begin_node_ = nullptr;
    end_node_ = nullptr;
    size_ = 0;
    std::swap(root_, other.root_);
    std::swap(begin_node_, other.begin_node_);
    std::swap(end_node_, other.end_node_);
    std::swap(size_, other.size_);
  }
  return *this;
}

template <class Key, class Value>
map<Key, Value>::map(const std::initializer_list<value_type> &items) {
  if (items.size()) {
    auto itr = items.begin();
    while (itr != items.end()) {
      insert(*itr);
      ++itr;
    }
  }
}

template <class Key, class Value>
map<Key, Value>::~map() {
  clear();
}

template <class Key, class Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() const {
  map<Key, Value>::iterator iterator;
  auto itr_node = begin_node_;
  iterator = *itr_node;
  return iterator;
}

template <class Key, class Value>
typename map<Key, Value>::iterator map<Key, Value>::end() const {
  map<Key, Value>::iterator iterator;
  auto itr_node = end_node_;
  iterator = *itr_node;
  return iterator;
}

template <class Key, class Value>
bool map<Key, Value>::empty() {
  return !size_;
}

template <class Key, class Value>
size_t map<Key, Value>::size() {
  return size_;
}

template <class Key, class Value>
typename map<Key, Value>::size_type map<Key, Value>::max_size() {
  std::allocator<Key> alloc;
  return alloc.max_size();
}

template <class Key, class Value>
void map<Key, Value>::clear() {
  if (root_) {
    delete_node(root_);
    size_ = 0;
    root_ = nullptr;
  }
}

template <class Key, class Value>
void map<Key, Value>::erase(map<Key, Value>::iterator pos) {
  if (pos.itr_node_ != nullptr) {
    if (pos.itr_node_ == begin_node_) {
      begin_node_ = pos.itr_node_->parent_;
    }
    if (pos.itr_node_->color_) {
      erase_red(pos);
    } else {
      erase_black(pos);
    }
    size_ -= 1;
  }
}

template <class Key, class Value>
void map<Key, Value>::swap(map &other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(begin_node_, other.begin_node_);
  std::swap(end_node_, other.end_node_);
}

template <class Key, class Value>
void map<Key, Value>::merge(map<Key, Value> &other) {
  for (auto itr = other.begin(); itr != other.end(); ++itr) {
    insert(*itr);
  }
}

template <class Key, class Value>
Value &map<Key, Value>::at(const Key &key) {
  iterator itr_found = find(key);
  if (itr_found == end()) {
    throw std::out_of_range("at::no such element in the map!");
  }
  return (*itr_found).second;
}

template <class Key, class Value>
Value &map<Key, Value>::operator[](const Key &key) {
  iterator itr_found = find(key);
  if (itr_found == end()) {
    auto insert_result_pair = insert(std::pair<Key, Value>(key, {}));
    return (*insert_result_pair.first).second;
  }
  return (*itr_found).second;
}

template <class Key, class Value>
bool map<Key, Value>::contains(const Key &key) {
  return find(key) != end();
}

template <class Key, class Value>
typename map<Key, Value>::iterator map<Key, Value>::find(const Key &key) {
  map<Key, Value>::iterator pos = end();
  for (map<Key, Value>::iterator itr = begin(); itr != end() && itr != pos;
       ++itr) {
    if (key == itr->first) {
      pos = itr;
    }
  }
  return pos;
}

template <class Key, class Value>
void map<Key, Value>::erase_black(map<Key, Value>::iterator pos) {
  if ((!pos.itr_node_->right_ || pos.itr_node_->right_ == end_node_) &&
      (!pos.itr_node_->left_ || pos.itr_node_->left_ == end_node_)) {
    node_ *parent = pos.itr_node_->parent_;
    erase_black_without_children(pos.itr_node_);
    balance_tree(parent);
  } else if (pos.itr_node_->right_ && pos.itr_node_->left_ &&
             pos.itr_node_->right_ != end_node_ &&
             pos.itr_node_->left_ != end_node_) {
    erase_node_with_two_children(pos.itr_node_);
  } else {
    erase_black_with_one_child(pos.itr_node_);
  }
}

template <class Key, class Value>
void map<Key, Value>::erase_black_with_one_child(map<Key, Value>::node_ *node) {
  if (node->left_ && (!node->right_ || node->right_ == end_node_)) {
    node->value_ = node->left_->value_;
    delete node->left_;
    node->left_ = nullptr;
  } else if (!node->left_ && node->right_ && node->right_ != end_node_) {
    node->value_ = node->right_->value_;
    delete node->right_;
    node->left_ = nullptr;
  }
}

template <class Key, class Value>
void map<Key, Value>::erase_black_without_children(
    map<Key, Value>::node_ *node) {
  node_ *parent = nullptr;
  node_ *brother = nullptr;
  node_ *l_nephew = nullptr;
  node_ *r_nephew = nullptr;

  if (node->parent_) {
    parent = node->parent_;
    if (parent->left_ == node && parent->right_) {
      brother = parent->right_;
    } else if (parent->right_ == node && parent->left_) {
      brother = parent->left_;
    }
    if (brother && brother->right_) {
      r_nephew = brother->right_;
    }
    if (brother && brother->left_) {
      l_nephew = brother->left_;
    }
    if (brother && !brother->color_) {
      if (r_nephew && l_nephew && (r_nephew->color_ || l_nephew->color_)) {
        if (l_nephew->color_ && (!r_nephew->color_ || r_nephew == end_node_)) {
          erase_black_without_children_and_black_brother_with_left_red_nephew(
              node, parent, brother);
        }
      } else if (((l_nephew && !l_nephew->color_) || !l_nephew) &&
                 ((r_nephew && !r_nephew->color_) || !r_nephew)) {
        erase_black_without_children_and_black_brother_with_black_nephews(
            node, parent, brother);
      }
    } else if (brother && brother->color_) {
      erase_black_without_children_and_red_brother(node, parent, brother);
    }
  }
}

template <class Key, class Value>
void map<Key, Value>::
    erase_black_without_children_and_black_brother_with_black_nephews(
        map<Key, Value>::node_ *node, map<Key, Value>::node_ *parent,
        map<Key, Value>::node_ *brother) {
  brother->color_ = true;

  if (!node->left_ && (!node->right_ || node->right_ == end_node_)) {
    if (parent->left_ == node) {
      parent->left_ = nullptr;
    } else if (parent->right_ == node) {
      parent->right_ = nullptr;
    }
    delete node;
  }

  if (!parent->color_) {
    erase_black_without_children(parent);
  }
  parent->color_ = false;
}

template <class Key, class Value>
void map<Key, Value>::erase_black_without_children_and_red_brother(
    map<Key, Value>::node_ *node, map<Key, Value>::node_ *parent,
    map<Key, Value>::node_ *brother) {
  brother->color_ = true;
  if (!node->left_ && (!node->right_ || node->right_ == end_node_)) {
    if (parent->left_ == node) {
      parent->left_ = nullptr;
    } else if (parent->right_ == node) {
      parent->right_ = nullptr;
    }
    if (node->right_ && node->right_ == end_node_) {
      end_node_->parent_ = node->parent_;
      node->parent_->right_ = end_node_;
    }
    delete node;
  }
  if (!parent->color_) {
    erase_black_without_children(parent);
  }
  parent->color_ = false;
}

template <class Key, class Value>
void map<Key, Value>::erase_red(map<Key, Value>::iterator pos) {
  if (!pos.itr_node_->left_ && !pos.itr_node_->right_) {
    erase_red_without_children(pos.itr_node_);
  } else if (pos.itr_node_->left_ && pos.itr_node_->right_) {
    erase_node_with_two_children(pos.itr_node_);
  }
}

template <class Key, class Value>
void map<Key, Value>::erase_red_without_children(map<Key, Value>::node_ *node) {
  if (node->parent_ && node->parent_->left_ == node) {
    node->parent_->left_ = nullptr;
  } else if (node->parent_ && node->parent_->right_ == node) {
    if (node->right_ && node->right_ == end_node_) {
      end_node_->parent_ = node->parent_;
      node->parent_->right_ = end_node_;
    } else {
      node->parent_->right_ = nullptr;
    }
  }
  delete node;
}

template <class Key, class Value>

void map<Key, Value>::erase_node_with_two_children(
    map<Key, Value>::node_ *node) {
  node_ *itr_node = node;
  if (itr_node->right_) {
    itr_node = itr_node->right_;
    while (itr_node->right_ && !itr_node->left_ &&
           itr_node->right_ != end_node_) {
      itr_node = itr_node->right_;
    }
    if (itr_node->left_) {
      itr_node = itr_node->left_;
    }
  }
  node->value_ = itr_node->value_;
  if (itr_node->color_) {
    erase_red_without_children(itr_node);
  } else {
    erase_black_without_children(itr_node);
  }
}

template <class Key, class Value>
void map<Key, Value>::
    erase_black_without_children_and_black_brother_with_left_red_nephew(
        map<Key, Value>::node_ *node, map<Key, Value>::node_ *parent,
        map<Key, Value>::node_ *brother) {
  std::swap(brother->color_, brother->left_->color_);
  right_turn(brother);
  erase_black_without_children_and_black_brother_with_right_red_nephew(
      node, parent, brother);
}

template <class Key, class Value>
void map<Key, Value>::
    erase_black_without_children_and_black_brother_with_right_red_nephew(
        map<Key, Value>::node_ *node, map<Key, Value>::node_ *parent,
        map<Key, Value>::node_ *brother) {
  brother->color_ = brother->parent_->color_;
  brother->parent_->color_ = false;
  brother->right_->color_ = false;
  left_turn(parent);
  if (parent->left_ == node) {
    parent->left_ = nullptr;
  } else if (parent->right_ == node) {
    parent->right_ = nullptr;
  }
  delete node;
}

template <class Key, class Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const Key &key, const Value &obj) {
  return insert(value_type(key, obj));
}

template <class Key, class Value>
std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert_or_assign(const Key &key, const Value &obj) {
  auto found = find(key);
  std::pair<iterator, bool> result(found, false);
  if (found == end()) {
    result = insert(key, obj);
  } else {
    (*found).second = obj;
    result.second = true;
  }
  return result;
}

template <class Key, class Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    value_type value) {
  bool status_of_insertion = false;
  if (!contains(value.first)) {
    if (!root_) {
      root_ = create_node(value, false);
      end_node_ = new node_;
      end_node_->left_ = nullptr;
      end_node_->right_ = nullptr;
      begin_node_ = root_;
      end_node_->parent_ = root_;
      root_->right_ = end_node_;
      size_ += 1;
    } else {
      node_ *new_node = create_node(value, true);
      node_ *itr = root_;
      // Emil
      while (!status_of_insertion) {
        if (value.first < (itr->value_).first) {
          if (!itr->left_) {
            itr->left_ = new_node;
            new_node->parent_ = itr;
            status_of_insertion = true;
            size_ += 1;
          } else {
            itr = itr->left_;
          }
        } else if (value.first > (itr->value_).first) {
          if (!itr->right_ || itr->right_ == end_node_) {
            itr->right_ = new_node;
            new_node->parent_ = itr;
            size_ += 1;
            status_of_insertion = true;
          } else {
            itr = itr->right_;
          }
        } else {
          // eq values
          break;
        }
      }
      balance_tree(new_node->parent_);
      update_side_nodes(new_node);
    }
  }
  return {find(value.first), status_of_insertion};
}

template <class Key, class Value>
typename map<Key, Value>::node_ *map<Key, Value>::create_node(
    const value_type value, bool is_red) {
  auto node = new node_;
  node->left_ = nullptr;
  node->right_ = nullptr;
  node->parent_ = nullptr;
  node->color_ = is_red;
  node->value_ = value;
  return node;
}

template <class Key, class Value>
void map<Key, Value>::delete_node(node_ *node) {
  if (node == nullptr) {
    return;
  }
  if (node->left_ != nullptr) {
    delete_node(node->left_);
  }
  if (node->right_) {
    delete_node(node->right_);
  }
  delete node;
}

template <class Key, class Value>
void map<Key, Value>::balance_tree(map<Key, Value>::node_ *node) {
  balance_node(node);
  if (node->parent_) {
    balance_tree(node->parent_);
  }
  root_->color_ = false;
}

template <class Key, class Value>
void map<Key, Value>::balance_node(map<Key, Value>::node_ *node) {
  bool is_balanced = false;
  while (!is_balanced && node != end_node_) {
    is_balanced = true;
    if (node && node->right_ && node->right_->color_) {
      left_turn(node);
      node = node->parent_;
      is_balanced = false;
    }
    if (node && node->left_ && node->left_->left_ && node->left_->color_ &&
        node->left_->left_->color_) {
      right_turn(node);
      node = node->parent_;
      is_balanced = false;
    }
    if (node && node->left_ && node->right_ && !node->color_ &&
        node->left_->color_ && node->right_->color_) {
      color_swap(node);
      is_balanced = false;
    }
  }
}

template <class Key, class Value>
void map<Key, Value>::right_turn(map<Key, Value>::node_ *node) {
  node_ *top_node = node;
  node_ *bottom_node = node->left_;
  bottom_node->color_ = top_node->color_;
  top_node->color_ = true;
  if (top_node == root_) {
    root_ = bottom_node;
  } else if (top_node->parent_->right_ == top_node) {
    top_node->parent_->right_ = bottom_node;
  } else if (top_node->parent_->left_ == top_node) {
    top_node->parent_->left_ = bottom_node;
  }

  if (bottom_node->right_) {
    bottom_node->right_->parent_ = top_node;
  }

  bottom_node->parent_ = top_node->parent_;
  top_node->parent_ = bottom_node;

  top_node->left_ = bottom_node->right_;
  bottom_node->right_ = top_node;

  node = bottom_node;
  node->right_ = top_node;
}

template <class Key, class Value>
void map<Key, Value>::left_turn(map<Key, Value>::node_ *node) {
  node_ *top_node = node;
  node_ *bottom_node = node->right_;

  bottom_node->color_ = top_node->color_;
  top_node->color_ = true;
  if (top_node == root_) {
    root_ = bottom_node;
  } else if (top_node->parent_->right_ == top_node) {
    top_node->parent_->right_ = bottom_node;
  } else if (top_node->parent_->left_ == top_node) {
    top_node->parent_->left_ = bottom_node;
  }

  if (bottom_node->left_) {
    bottom_node->left_->parent_ = top_node;
  }

  bottom_node->parent_ = top_node->parent_;
  top_node->parent_ = bottom_node;
  top_node->right_ = bottom_node->left_;
  bottom_node->left_ = top_node;
  node = bottom_node;
  node->left_ = top_node;
}

template <class Key, class Value>
void map<Key, Value>::color_swap(map<Key, Value>::node_ *node) {
  node->color_ = true;
  node->left_->color_ = false;
  node->right_->color_ = false;
}

template <class Key, class Value>
void map<Key, Value>::update_side_nodes(node_ *node) {
  if (begin_node_->value_.first > node->value_.first) {
    begin_node_ = node;
  }
  if (end_node_->parent_->value_.first < node->value_.first) {
    if (end_node_->parent_->right_ == end_node_) {
      end_node_->parent_->right_ = nullptr;
    }
    end_node_->parent_ = node;
    node->right_ = end_node_;
  }
}

template <class Key, class Value>
void map<Key, Value>::iterator::operator=(node_ &node_) {
  itr_node_ = &node_;
}

template <class Key, class Value>
typename map<Key, Value>::value_type &map<Key, Value>::iterator::operator*() {
  return itr_node_->value_;
}

template <class Key, class Value>
typename map<Key, Value>::value_type *map<Key, Value>::iterator::operator->() {
  return &(itr_node_->value_);
}

template <class Key, class Value>
void map<Key, Value>::iterator::operator++() {
  if (itr_node_ && itr_node_->right_) {
    itr_node_ = itr_node_->right_;
    while (itr_node_ && itr_node_->left_) {
      itr_node_ = itr_node_->left_;
    }
  } else if (itr_node_->parent_) {
    node_ *parent_itr_node = itr_node_->parent_;
    while (itr_node_->parent_ && itr_node_->parent_->right_ == itr_node_) {
      itr_node_ = itr_node_->parent_;
      parent_itr_node = parent_itr_node->parent_;
    }
    itr_node_ = parent_itr_node;
  }
}

template <class Key, class Value>
void map<Key, Value>::iterator::operator--() {
  if (itr_node_->left_) {
    itr_node_ = itr_node_->left_;
    while (itr_node_->right_) {
      itr_node_ = itr_node_->right_;
    }
  } else {
    node_ *parent_itr_node = itr_node_->parent_;
    while (itr_node_->parent_ && itr_node_->parent_->left_ == itr_node_) {
      itr_node_ = itr_node_->parent_;
      parent_itr_node = parent_itr_node->parent_;
    }
    itr_node_ = parent_itr_node;
  }
}

template <class Key, class Value>
bool map<Key, Value>::iterator::operator!=(map<Key, Value>::iterator iterator) {
  return itr_node_ != iterator.itr_node_;
}

template <class Key, class Value>
bool map<Key, Value>::iterator::operator==(map<Key, Value>::iterator iterator) {
  return itr_node_ == iterator.itr_node_;
}
}  // namespace s21
