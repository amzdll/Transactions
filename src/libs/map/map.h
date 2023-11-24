#ifndef TRANSACTIONS_SRC_LIBS_MAP_MAP_H_
#define TRANSACTIONS_SRC_LIBS_MAP_MAP_H_

#include <initializer_list>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "iostream"
#include "string"

namespace s21 {
template <class Key, class Value>
class map {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<Key, mapped_type>;
  using reference = const value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  class iterator;

  struct node_ {
    node_ *left_;
    node_ *right_;
    node_ *parent_;
    value_type value_;
    bool color_;
  };

  map();
  map(const map &other);
  map(std::initializer_list<value_type> const &items);
  map(map &&other) noexcept;
  map &operator=(map &&other) noexcept;
  ~map();

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  void erase(s21::map<Key, Value>::iterator pos);
  void swap(map &other);
  void merge(map &other);

  Value &at(const Key &key);
  Value &operator[](const Key &key);

  bool contains(const Key &key);
  iterator find(const Key &key);

  std::pair<iterator, bool> insert(value_type value);
  std::pair<iterator, bool> insert(const Key &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key,
                                             const mapped_type &obj);

 private:
  node_ *create_node(value_type value, bool is_red);
  void update_side_nodes(node_ *node);
  void balance_tree(map<Key, Value>::node_ *node);
  void balance_node(map<Key, Value>::node_ *node);
  void color_swap(map<Key, Value>::node_ *node);
  void right_turn(map<Key, Value>::node_ *node);
  void left_turn(map<Key, Value>::node_ *node);
  void erase_black(s21::map<Key, Value>::iterator pos);
  void erase_red(s21::map<Key, Value>::iterator pos);
  void erase_red_without_children(s21::map<Key, Value>::node_ *node);
  void erase_node_with_two_children(s21::map<Key, Value>::node_ *node);
  void erase_black_with_one_child(s21::map<Key, Value>::node_ *node);
  void erase_black_without_children(s21::map<Key, Value>::node_ *node);
  void erase_black_without_children_and_black_brother_with_right_red_nephew(
      s21::map<Key, Value>::node_ *node, s21::map<Key, Value>::node_ *parent,
      s21::map<Key, Value>::node_ *brother);
  void erase_black_without_children_and_black_brother_with_left_red_nephew(
      s21::map<Key, Value>::node_ *node, s21::map<Key, Value>::node_ *parent,
      s21::map<Key, Value>::node_ *brother);
  void erase_black_without_children_and_black_brother_with_black_nephews(
      s21::map<Key, Value>::node_ *node, s21::map<Key, Value>::node_ *parent,
      s21::map<Key, Value>::node_ *brother);
  void erase_black_without_children_and_red_brother(
      s21::map<Key, Value>::node_ *node, s21::map<Key, Value>::node_ *parent,
      s21::map<Key, Value>::node_ *brother);
  void delete_node(node_ *node);

  node_ *root_ = nullptr;
  node_ *begin_node_ = nullptr;
  node_ *end_node_ = nullptr;
  size_type size_ = 0;
};

template <class Key, class Value>
class map<Key, Value>::iterator {
 public:
  iterator() = default;

  value_type &operator*();
  void operator++();
  void operator--();
  bool operator==(map<Key, Value>::iterator iterator);
  void operator=(node_ &node_);
  bool operator!=(map<Key, Value>::iterator iterator);
  value_type *operator->();

  friend class map;

 protected:
  node_ *itr_node_ = nullptr;
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_LIBS_MAP_MAP_H_
