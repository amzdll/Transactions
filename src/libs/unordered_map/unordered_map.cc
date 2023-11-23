#include "unordered_map.h"

#include <bitset>
#include <string>
#include <type_traits>

namespace s21 {
// Constructors
template <class Key, class Value>
unordered_map<Key, Value>::unordered_map() {
  static_assert(!(std::is_same<Key, char>::value) &&
                    (std::is_arithmetic<Key>::value ||
                     std::is_same<Key, std::string>::value),
                "Not an arithmetic type or std::string");

  size_t buckets_size = 10;
  for (int i = 0; i < buckets_size; ++i) {
    std::list<value_type> bucket(0);
    buckets_.push_back(bucket);
  }
  std::list<value_type> dummy_bucket;
  dummy_bucket.push_back({});
  buckets_.push_back(dummy_bucket);
}

// Element Access
template <class Key, class Value>
Value &unordered_map<Key, Value>::operator[](const Key &key) {
  iterator iterator = find(key);
  if (iterator == end()) {
    auto insert_result_pair = insert(std::pair<Key, Value>(key, {}));
    return (*insert_result_pair.first).second;
  }
  return (*iterator).second;
}

// Iterator
template <class Key, class Value>
typename unordered_map<Key, Value>::iterator
unordered_map<Key, Value>::begin() {
  iterator iterator{};
  if (empty()) {
    return iterator;
  }

  for (auto itr = buckets_.begin(); itr != buckets_.end(); ++itr) {
    if (!itr->empty()) {
      iterator.bucket_itr_ = itr->begin();
      iterator.vector_itr_ = itr;
      iterator.value_ = *iterator.bucket_itr_;
      return iterator;
    }
  }
  return {};
}

template <class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::end() {
  iterator iterator{};
  if (!empty()) {
    iterator.vector_itr_ = --buckets_.end();
    iterator.bucket_itr_ = iterator.vector_itr_->begin();
  }
  return iterator;
}

// Capacity
template <class Key, class Value>
bool unordered_map<Key, Value>::size() const {
  return size_;
}

template <class Key, class Value>
bool unordered_map<Key, Value>::empty() const {
  return !size_;
}

template <class Key, class Value>
std::pair<typename unordered_map<Key, Value>::iterator, bool>
unordered_map<Key, Value>::insert(const unordered_map::value_type &value) {
  iterator iterator{};
  bool inserted = false;
  if (find(value.first) == end()) {
    buckets_[hash(value.first)].push_back(value);
    ++size_;
    inserted = true;
  }
  return {iterator, inserted};
}

// Modifiers
template <class Key, class Value>
void unordered_map<Key, Value>::clear() {}

template <class Key, class Value>
void unordered_map<Key, Value>::erase(unordered_map::iterator pos) {
  pos.vector_itr_->erase(pos.bucket_itr_);
}

template <class Key, class Value>
void unordered_map<Key, Value>::swap(unordered_map<Key, Value> &other) {
  std::swap(buckets_, other.buckets_);
  std::swap(size_, other.size_);
}

// Lookup
template <class Key, class Value>
bool unordered_map<Key, Value>::contains(const Key &key) {
  return find(key) != end();
}

// Bucket Interface
template <class Key, class Value>
size_t unordered_map<Key, Value>::bucket_count() {
  return buckets_.size();
}

// Additional
template <class Key, class Value>
typename unordered_map<Key, Value>::iterator unordered_map<Key, Value>::find(
    const Key &key) {
  int hash_key = hash(key);
  unordered_map<Key, Value>::iterator iterator = end();
  for (auto itr = buckets_[hash_key].begin(); itr != buckets_[hash_key].end();
       ++itr) {
    if (key == itr->first) {
      iterator.value_ = *itr;
      iterator.bucket_itr_ = itr;
      return iterator;
    }
  }
  return iterator;
}

template <class Key, class Value>
size_t unordered_map<Key, Value>::hash(Key key) {
  if constexpr (std::is_same<Key, std::string>::value) {
    return hash_string(key);
  } else {
    return hash_numeric(key);
  }
}

template <class Key, class Value>
size_t unordered_map<Key, Value>::hash_numeric(Key key) {
  std::bitset<sizeof(Key) * 8> bits(key);
  return (key ^ (key << 13) * bits.count()) % buckets_.capacity();
}

template <class Key, class Value>
size_t unordered_map<Key, Value>::hash_string(Key key) {
  int data_to_hash = 0;
  for (auto c : key) {
    data_to_hash += c;
  }
  std::bitset<sizeof(Key) * 8> bits(data_to_hash);
  return (data_to_hash ^ (data_to_hash << 13) * bits.count()) % buckets_.capacity();
}

// Iterator
template <class Key, class Value>
typename unordered_map<Key, Value>::iterator &
unordered_map<Key, Value>::iterator::operator=(
    const typename unordered_map<Key, Value>::iterator itr) {
  bucket_itr_ = itr.bucket_itr_;
  vector_itr_ = itr.vector_itr_;
}

template <class Key, class Value>
bool unordered_map<Key, Value>::iterator::operator==(
    const typename unordered_map<Key, Value>::iterator itr) {
  return itr.vector_itr_ == vector_itr_ && bucket_itr_ == itr.bucket_itr_;
}

template <class Key, class Value>
bool unordered_map<Key, Value>::iterator::operator!=(
    const typename unordered_map<Key, Value>::iterator itr) {
  return !(*this == itr);
}

template <class Key, class Value>
void unordered_map<Key, Value>::iterator::operator++() {
  ++bucket_itr_;
  if (bucket_itr_ == vector_itr_->end()) {
    ++vector_itr_;
    for (; vector_itr_->empty(); ++vector_itr_) {
    }
    bucket_itr_ = vector_itr_->begin();
    value_ = *(vector_itr_->begin());
  } else {
    value_ = *bucket_itr_;
  }
}

template <class Key, class Value>
void unordered_map<Key, Value>::iterator::operator--() {}

template <class Key, class Value>
typename unordered_map<Key, Value>::value_type &
unordered_map<Key, Value>::iterator::operator*() {
  return *bucket_itr_;
}

template <class Key, class Value>
typename unordered_map<Key, Value>::value_type *
unordered_map<Key, Value>::iterator::operator->() {
  return &(*bucket_itr_);
}
}  // namespace s21