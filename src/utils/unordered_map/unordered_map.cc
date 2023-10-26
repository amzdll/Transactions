#include "unordered_map.h"

#include <type_traits>
#include <string>
#include <bitset>

#include "iostream"

namespace s21 {
// Constructors
template<class Key, class Value>
unordered_map<Key, Value>::unordered_map() : buckets_(10) {
  static_assert(!(std::is_same<Key, char>::value) &&
                    (std::is_arithmetic<Key>::value ||
                        std::is_same<Key, std::string>::value),
                "Not an arithmetic type or std::string");
}

// Iterator
template<class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::begin() const {
  for (size_t i = 0; i < buckets_.size(); ++i) {
    if (!buckets_[i].empty()) {
      return buckets_[i].begin();
    }
  }
  return {};
}

template<class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::end() const {
  for (size_t i = buckets_.size() - 1; i > 0; --i) {
    if (!buckets_[i].empty()) {
      return buckets_[i].end();
    }
  }
  return {};
}

// Capacity
template<class Key, class Value>
bool unordered_map<Key, Value>::size() {
  return size_;
}

template<class Key, class Value>
bool unordered_map<Key, Value>::empty() {
  return !size_;
}

template<class Key, class Value>
bool unordered_map<Key, Value>::insert(const unordered_map::value_type &value) {
  bool inserted = !find_key(value.first);
  if (inserted) {
    buckets_[hash_numeric(value.first)].push_back(value);
  }
  return inserted;
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
  int hash_key = hash(key);
  auto pos = buckets_[hash_key].begin();
  for (; pos != buckets_[hash_key].end(); ++pos) {
    if (key == pos->first) {
      return pos;
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

}  // namespace s21


int main() {
  s21::unordered_map<int, int> a;
  a.insert({1, 1});
//  std::vector<std::list<int>> a(10);
////  auto b = a.end();
////  --b;
//  for (int i = 0; i < a.size(); ++i) {
//    std::cout << a[i].empty() << " ";
//  }
//  std::cout << *b;
  return 0;
}