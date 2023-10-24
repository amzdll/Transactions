#include "../include/hash_table.h"

#include "map"
#include <bitset>

namespace s21 {

template<class Key, class Value>
HashTable<Key, Value>::HashTable() : buckets_(10) {
  static_assert(
      !(std::is_same<Key, char>::value) &&
          (std::is_arithmetic<Key>::value || std::is_same<Key, std::string>::value),
      "Not an arithmetic type or std::string");
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::Set(Key key, Value value) {
  bool is_exist = !Exists(key);
  if (!is_exist) {
    buckets_[Hash(key)].push_back({key, value});
  }
  return is_exist;
}

template<typename Key, typename Value>
Value HashTable<Key, Value>::Get(Key key) {
  bool is_find = false;
  int hash_key = Hash(key);
  Value value = {};
  for (auto itr = buckets_[hash_key].begin(); itr != buckets_[hash_key].end() && !is_find; ++itr) {
    if (key == itr->first) {
      is_find = true;
      value = itr->second;
    }
  }
  return value;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::Exists(Key key) {
  bool is_exists = false;
  int hash_key = Hash(key);
  for (auto itr = buckets_[hash_key].begin(); itr != buckets_[hash_key].end() && !is_exists; ++itr) {
    if (key == itr->first) {
      is_exists = true;
    }
  }
  return is_exists;
}

template<class Key, class Value>
size_t HashTable<Key, Value>::Hash(Key key) {
  if constexpr (std::is_same_v<Key, std::string>) {
    return HashString(key);
  } else {
    return HashNumeric(key);
  }
}

template<class Key, class Value>
size_t HashTable<Key, Value>::HashNumeric(Key key) {
//  std::cout << "numeric" << std::endl;
  std::bitset<sizeof(Key) * 8> bits(key);
  return (key ^ (key << 13) * bits.count()) % buckets_.capacity();
}

template<class Key, class Value>
size_t HashTable<Key, Value>::HashString(std::string key) {
  std::cout << "string" << std::endl;
  return 0;
}

}  // namespace s21

int main() {
//  s21::HashTable<std::string , int> hs;
//  std::map<int, int> map;
//  for (int i = 0; i < 100; ++i) {
//    map[hs.Hash(std::to_string(i))] = map[hs.Hash(std::to_string(i))] + 1;
//  }

  s21::HashTable<std::string, int> hs;
  s21::HashTable<int, int> hs1;

  std::map<int, int> map;
  hs1.Hash(1);
  for (int i = 0; i < 10; ++i) {
    map[hs1.Hash(i)] = map[hs1.Hash((i))] + 1;
  }
  hs1.Set(2, 1);
  hs1.Set(1, 1);
  hs1.Set(3, 1);
  hs1.Set(4, 1);
//  hs1.Set(2,1);
  hs1.Set(5, 1);
  hs1.Set(6, 1);
  hs1.Set(7, 3);
  std::cout << hs1.Get(7);
//  hs1.print();
//  for (auto itr : map) {
//    std::cout << itr.first << " : " << itr.second << std::endl;
//  }
//  std::cout << map.size();
}