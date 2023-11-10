#include "unordered_map.h"

#include <type_traits>
#include <string>
#include <bitset>

#include "iostream"

namespace s21 {
// Constructors
template<class Key, class Value>
unordered_map<Key, Value>::unordered_map() {
  static_assert(!(std::is_same<Key, char>::value) &&
                    (std::is_arithmetic<Key>::value ||
                        std::is_same<Key, std::string>::value),
                "Not an arithmetic type or std::string");

  size_t buckets_size = 10;
  for (size_t i = 0; i < buckets_size; ++i) {
    buckets_.push_back(new std::list<value_type>{});
  }
}

// Iterator
template<class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::begin() const {
  iterator iterator{};
  if (empty()) {
    return iterator;
  }

  for (size_t i = 0; i < buckets_.size(); ++i) {
    if (!buckets_[i]->empty()) {
      iterator.bucket_index = i;
      iterator.bucket_itr = buckets_[i]->begin();
      iterator.vec_itr = ;
      auto z = buckets_.begin() + i;

      return iterator;
    }
  }
}


template<class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::end() const {
  iterator iterator{};
  if (empty()) {
    return iterator;
  }

  for (size_t i = buckets_.size() - 1; i > 0; --i) {
    if (!buckets_[i]->empty()) {
      iterator.bucket_index = i;
      iterator.bucket_itr = buckets_[i]->end();
      return iterator;
    }
  }
  return {};
}

// Capacity
template<class Key, class Value>
bool unordered_map<Key, Value>::size() const {
  return size_;
}

template<class Key, class Value>
bool unordered_map<Key, Value>::empty() const {
  return !size_;
}

template<class Key, class Value>
bool unordered_map<Key, Value>::insert(const unordered_map::value_type &value) {

//  bool inserted = !find_key(value.first);
//  if (inserted) {
  buckets_[hash_numeric(value.first)]->push_back(value);
  ++size_;
//  }
  return true;
}

// Lookup
template<class Key, class Value>
bool unordered_map<Key, Value>::contains(const value_type &value) {
  return find_key(value.first)->second == value.second;
//  int hash_key = Hash(value.first);
//  auto pos = buckets_[hash_key].begin();
//  for (; pos != buckets_[hash_key].end(); ++pos) {
//    if (value.first == pos->first) {
//      return true;
//    }
//  }
//  return false;
}

// Additional
template<class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::find_key(const Key &key) {
  unordered_map<Key, Value>::iterator iterator;
  int hash_key = hash(key);
  auto pos = buckets_[hash_key]->begin();
  for (; pos != buckets_[hash_key]->end(); ++pos) {
    if (key == pos->first) {
      iterator.bucket_itr = pos;
      iterator.bucket_index = hash_key;
      return iterator;
    }
  }
  return {};
}

template<class Key, class Value>
size_t unordered_map<Key, Value>::hash(Key key) {
  if constexpr (std::is_same_v<Key, std::string>) {
    return hash_string(key);
  } else {
    return hash_numeric(key);
  }
}

template<class Key, class Value>
size_t unordered_map<Key, Value>::hash_numeric(Key key) {
  std::bitset<sizeof(Key) * 8> bits(key);
  return (key ^ (key << 13) * bits.count()) % buckets_.capacity();
}

template<class Key, class Value>
size_t unordered_map<Key, Value>::hash_string(Key key) {
  std::cout << "string" << std::endl;
  return 0;
}


// Iterator

template<class Key, class Value>
typename unordered_map<Key, Value>::iterator &
unordered_map<Key, Value>::iterator::operator=(const typename unordered_map<Key, Value>::iterator itr) {
  bucket_index = itr.bucket_index;
  bucket_itr = itr.bucket_itr;
  vec_itr = itr.vec_itr;
}

template<class Key, class Value>
bool unordered_map<Key, Value>::iterator::operator==(const typename unordered_map<Key, Value>::iterator itr) {
  return bucket_index == itr.bucket_index && bucket_itr == itr.bucket_itr;
}

template<class Key, class Value>
bool unordered_map<Key, Value>::iterator::operator!=(const typename unordered_map<Key, Value>::iterator itr) {
  return bucket_index != itr.bucket_index || bucket_itr != itr.bucket_itr;
}

template<class Key, class Value>
typename unordered_map<Key, Value>::iterator &
unordered_map<Key, Value>::iterator::operator++() {
  ++bucket_itr;
//  if (bucket_itr != buckets_)
}

}  // namespace s21


int main() {
  s21::unordered_map<int, int> a;
  a.insert({1, 1});
  a.insert({2, 2});

  auto b = a.begin();
  auto e = a.end();

  for (; b != e; ++b) {

  }

  return 0;
}