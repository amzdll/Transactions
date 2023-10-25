#include "../include/hash_table.h"

#include <bitset>

#include "map"

namespace s21 {
template <class Key, class Value>
HashTable<Key, Value>::HashTable() : buckets_(10) {
  static_assert(!(std::is_same<Key, char>::value) &&
                    (std::is_arithmetic<Key>::value ||
                     std::is_same<Key, std::string>::value),
                "Not an arithmetic type or std::string");
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::Set(Key key, Value value) {
  bool inserted = !Exists(key);
  if (inserted) {
    buckets_[Hash(key)].push_back({key, value});
  }
  return inserted;
}

template <typename Key, typename Value>
Value HashTable<Key, Value>::Get(Key key) {
  int hash_key = Hash(key);
  auto pos = buckets_[hash_key].begin();
  for (; pos != buckets_[hash_key].end(); ++pos) {
    if (key == pos->first) {
      return pos->second;
    }
  }
  return Value{};
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::Exists(Key key) {
  bool is_exist = false;
  int hash_key = Hash(key);
  auto pos = buckets_[hash_key].begin();
  for (; pos != buckets_[hash_key].end() && !is_exist; ++pos) {
    if (key == pos->first) {
      is_exist = true;
    }
  }
  return is_exist;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::Del(Key key) {
  bool is_deleted = false;
  int hash_key = Hash(key);
  auto pos = buckets_[hash_key].begin();
  for (; pos != buckets_[hash_key].end() && !is_deleted; ++pos) {
    if (key == pos->first) {
      buckets_[hash_key].erase(pos);
      is_deleted = true;
    }
  }
  return is_deleted;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::Update(Key key, Value value) {
  bool is_updated = false;
  int hash_key = Hash(key);
  auto pos = buckets_[hash_key].begin();
  for (; pos != buckets_[hash_key].end() && !is_updated; ++pos) {
    if (key == pos->first) {
      is_updated = true;
      pos->second = value;
    }
  }
}

template <typename Key, typename Value>
std::vector<Key> HashTable<Key, Value>::Keys() {
  std::vector<Key> keys{};
  for (int i = 0; i < buckets_.size(); ++i) {
    for (auto itr : buckets_[i]) {
      keys.push_back(itr.first);
    }
  }
  return keys;
}

template <typename Key, typename Value>
std::vector<Key> HashTable<Key, Value>::Find(Value value) {
  std::vector<Key> keys{};
  for (int i = 0; i < buckets_.size(); ++i) {
    for (auto itr : buckets_[i]) {
      if (itr.second == value) {
        keys.push_back(itr.first);
      }
    }
  }
  return keys;
}

template <typename Key, typename Value>
std::vector<Value> HashTable<Key, Value>::ShowAll() {
  std::vector<Value> values{};
  for (int i = 0; i < buckets_.size(); ++i) {
    for (auto itr : buckets_[i]) {
      values.push_back(itr.second);
    }
  }
  return values;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::Rename(Key old_name, Key new_name) {
  bool is_renamed = false;
  if (!Exists(new_name)) {
    int hash_key = Hash(old_name);
    auto pos = buckets_[hash_key].begin();
    for (; pos != buckets_[hash_key].end() && !is_renamed; ++pos) {
      if (old_name == pos->first) {
        is_renamed = true;
        pos->first = new_name;
      }
    }
  }
  return is_renamed;
}

template <class Key, class Value>
size_t HashTable<Key, Value>::Hash(Key key) {
  if constexpr (std::is_same_v<Key, std::string>) {
    return HashString(key);
  } else {
    return HashNumeric(key);
  }
}

template <class Key, class Value>
size_t HashTable<Key, Value>::HashNumeric(Key key) {
  std::bitset<sizeof(Key) * 8> bits(key);
  return (key ^ (key << 13) * bits.count()) % buckets_.capacity();
}

template <class Key, class Value>
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
  hs1.Set(1, 1);
  hs1.Set(2, 1);
  hs1.Set(3, 1);
  hs1.Set(4, 1);
  hs1.Set(5, 1);
  hs1.Set(6, 1);
  hs1.Set(7, 3);
  hs1.Set(7, 3);
  hs1.Set(8, 3);
  hs1.Set(9, 12);
  //  std::cout << hs1.Get(9);
  hs1.Del(5);
  hs1.Update(9, 31);
  hs1.Rename(9, 52);
  //  hs1.print();
  s21::HashTable<int, s21::PersonalData> hs3;
  hs3.Set(1, {"a", "a", "a", "a", "a"});
  hs3.Set(2, {"a", "b", "b", "b", "b"});
  hs3.Set(3, {"c", "c", "c", "c", "c"});
  hs3.Update(3, {"-", "-", "hui", "-", "gvfd"});
  auto z = hs3.ShowAll();
  for (int i = 0; i < z.size(); ++i) {
    std::cout << z[i].name << " ";
    std::cout << z[i].surname << " ";
    std::cout << z[i].year << " ";
    std::cout << z[i].city << " ";
    std::cout << z[i].coins << " ";
    std::cout << std::endl;
  }
  auto k = hs1.Find(1);
  for (int i = 0; i < k.size(); ++i) {
    std::cout << k[i] << " ";
  }
  //  std::cout << std::endl;
  //  auto v = hs1.ShowAll();
  //  for (int i = 0; i < v.size(); ++i) {
  //    std::cout << v[i] << std::endl;
  //  }

  //  for (auto itr : map) {
  //    std::cout << itr.first << " : " << itr.second << std::endl;
  //  }
  //  std::cout << map.size();
}