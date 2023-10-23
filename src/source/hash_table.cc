#include "../include/hash_table.h"

namespace s21 {

template <class Key, class Value>
HashTable<Key, Value>::HashTable() {
  buckets_.reserve(10);
}



}  // namespace s21