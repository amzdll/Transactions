#ifndef TRANSACTIONS_SRC_UTILS_UNSORTED_MAP_UNSORTED_MAP_H_
#define TRANSACTIONS_SRC_UTILS_UNSORTED_MAP_UNSORTED_MAP_H_

#include <iostream>
#include <list>
#include <vector>

namespace s21 {
template <class Key, class Value>
class unordered_map {
 public:
  // Members type
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = const value_type &;
  using const_reference = const value_type &;
  class iterator;
  using size_type = std::size_t;
  using buckets = std::vector<std::list<value_type>>;
  friend class iterator;

  // Constructors
  unordered_map();
  // unordered_map(std::initializer_list<value_type> const &items);
  // unordered_map(const unordered_map &m);
  // unordered_map(unordered_map &&m) noexcept;
  ~unordered_map() = default;
  // void operator=(unordered_map &&m);

  // Element access
  //   Value &at(const Key &key);
  Value &operator[](const Key &key);

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty() const;
  bool size() const;

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(unordered_map<Key, Value> &other);
  //  void merge(tree &other);

  // Lookup
  bool contains(const Key &key);
  iterator find(const Key &key);

  // Bucket interface
  size_type bucket_count();

 protected:
  buckets buckets_;
  size_type size_ = 0;

  size_type hash(Key key);
  size_type hash_numeric(Key key);
  size_type hash_string(Key key);
};

template <class Key, class Value>
class unordered_map<Key, Value>::iterator {
 public:
  friend class unordered_map;

  iterator() = default;
  ~iterator() = default;

  value_type &operator*();
  void operator++();
  void operator--();
  bool operator==(iterator itr);
  bool operator!=(iterator itr);
  iterator &operator=(iterator itr);
  value_type *operator->();

 private:
  value_type value_ = {};
  typename buckets::iterator vector_itr_ = {};
  typename std::list<value_type>::iterator bucket_itr_ = {};
};

}  // namespace s21
#endif  // TRANSACTIONS_SRC_UTILS_UNSORTED_MAP_UNSORTED_MAP_H_
