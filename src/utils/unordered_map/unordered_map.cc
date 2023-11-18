#include "unordered_map.h"

#include <type_traits>
#include <string>
#include <bitset>
#include <iostream>
#include <typeinfo>

#include <unordered_map>

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
  buckets_.push_back(nullptr);
}

// Iterator
template<class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::begin() {
  iterator iterator{};
  if (empty()) {
    return iterator;
  }

  for (auto itr = buckets_.begin(); itr != buckets_.end(); ++itr) {
    if (!(*itr)->empty()) {
      iterator.bucket_itr = (*(*itr)).begin();
      iterator.vec_itr = itr;
      iterator.value_ = *iterator.bucket_itr;
      return iterator;
    }
  }

  return {};
}

template<class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::end() {
  iterator iterator{};
  if (!empty()) {
     iterator.vec_itr = --buckets_.end();
  }

//  for (auto itr = --buckets_.end(); --itr != buckets_.begin();) {
//    if (!(*itr)->empty()) {
//      ++itr;
//      iterator.vec_itr = itr;
//      return iterator;
//    }
//  }
  return iterator;
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
//  if constexpr (std::is_same<Key, std::string>) {
//    return hash_string(key);
//  } else {
//    return hash_numeric(key);
//  }
  return {};
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
  bucket_itr = itr.bucket_itr;
  vec_itr = itr.vec_itr;
}

template<class Key, class Value>
bool unordered_map<Key, Value>::iterator::operator==(const typename unordered_map<Key, Value>::iterator itr) {
  return itr.vec_itr == vec_itr && bucket_itr == itr.bucket_itr;
//  return *vec_itr == *itr.vec_itr && *bucket_itr == *(itr.bucket_itr);
}

template<class Key, class Value>
bool unordered_map<Key, Value>::iterator::operator!=(const typename unordered_map<Key, Value>::iterator itr) {
  std::cout << this->value_.first << " " << this->value_.first << "   ";
  std::cout << itr->first << " " << itr->second << std::endl;
  return !(itr == *this);
}

// { (1) (2 )  () ()  () () () () (7 end) () () }



template<class Key, class Value>
void unordered_map<Key, Value>::iterator::operator++() {
  ++bucket_itr;
  if (*vec_itr) {
    return;
  }

  if (bucket_itr == (*vec_itr)->end()) {
    ++vec_itr;
    for (; *vec_itr; ++vec_itr) {
      if (!(*vec_itr)->empty()) {
        bucket_itr = (*vec_itr)->begin();
        value_ = *((*vec_itr)->begin());
        return;
      }
    }
  }
}

template<class Key, class Value>
void unordered_map<Key, Value>::iterator::operator--() {
}

template<class Key, class Value>
typename unordered_map<Key, Value>::value_type &unordered_map<Key, Value>::iterator::operator*() {
  return value_;
}

template<class Key, class Value>
typename unordered_map<Key, Value>::value_type *unordered_map<Key, Value>::iterator::operator->() {
  return &(value_);
}

}  // namespace s21


int main() {
  s21::unordered_map<int, int> a;
  std::unordered_map<int, int> b(2);
  auto fsd = b.end();
  std::cout << fsd->first << std::endl;
//  a.insert({1, 1});
//  a.insert({2, 2});
//  auto e = a.begin();
//
////  *e;
////  std::cout << e->first << std::endl;
//  int z = 0;
//  for (auto itr = a.begin(); itr != a.end(); ++itr) {
////    ++z;
////    std::cout << itr->first << " " << itr->second << std::endl;
//  }
  return 0;
}