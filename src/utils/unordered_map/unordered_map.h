#ifndef TRANSACTIONS_SRC_UTILS_UNSORTED_MAP_UNSORTED_MAP_H_
#define TRANSACTIONS_SRC_UTILS_UNSORTED_MAP_UNSORTED_MAP_H_

#include <memory>

#include <list>
#include <vector>
namespace s21 {
template<class Key, class Value>
class unordered_map {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = const value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using bucket = std::list<value_type> *;

  class iterator;
  friend class iterator;
  // Constructors

  unordered_map();
//  unordered_map(std::initializer_list<value_type> const &items);
//  unordered_map(const unordered_map &m);
//  unordered_map(unordered_map &&m) noexcept;
  ~unordered_map() = default;
//  void operator=(unordered_map &&m);

// Iterator
  iterator begin();
  iterator end();

// Capacity
  bool empty() const;
  bool size() const;

// Modifiers
//  void clear();
  bool insert(const value_type &value);
//  void erase(unsorted_map<Key>::iterator pos);
//  void swap(tree &other);
//  void merge(tree &other);
//
// Lookup
  bool contains(const value_type &value);
//  iterator find(const Key &key);
//
//  T &at(const Key &key);
//  T &operator[](const Key &key);

 protected:
  std::vector<std::list<value_type> *> buckets_;
  size_type size_ = 0;

//  typename std::vector<bucket>::iterator begin_{};
//  typename std::vector<bucket>::iterator end_{};

  typename std::list<value_type>::iterator begin_{};
  typename std::list<value_type>::iterator end_{};

  size_type hash(Key key);
  size_type hash_string(Key key);
  size_type hash_numeric(Key key);
  iterator find_key(const Key &key);
};

template<class Key, class Value>
class unordered_map<Key, Value>::iterator {
 public:
  friend class unordered_map;

  iterator() = default;
  ~iterator() = default;

  bool operator==(const iterator itr);
  bool operator!=(const iterator itr);
  iterator& operator=(const iterator itr);
  iterator& operator++();


 private:
//  typename std::vector<bucket>::iterator vec_itr_ = {};
  int bucket_index = 0;
  typename std::list<value_type>::iterator bucket_itr = {};
  typename std::vector<std::list<value_type> *>::iterator vec_itr = {};
};


}  // namespace s21
#endif  // TRANSACTIONS_SRC_UTILS_UNSORTED_MAP_UNSORTED_MAP_H_
