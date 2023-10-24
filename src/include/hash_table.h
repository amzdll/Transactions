#ifndef TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
#define TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
#include "iostream"

#include "abstract_storage.h"
#include <type_traits>

#include <vector>
#include <list>

namespace s21 {
template<typename Key, typename Value>
class HashTable : AbstractStorage<Key, Value> {
 public:
  using bucket = std::list<std::pair<Key, Value>>;

  HashTable();
//  ~HashTable();
//
  void print();
  bool Set(Key key, Value value) override;
  Value Get(Key key) override;
  bool Exists(Key key) override;
  bool Del(Key key) override;
//  void Update() override;
//  std::vector<std::string> Keys() override;
//  void Rename(Key old_name, Key new_name) override;
//  unsigned int TTL(Key key) override;
//  std::vector<Key> Find(Value) override;
//  std::vector<Value> ShowAll() override;
//  int Upload(std::string file_path) override;
//  int Export(std::string file_path) override;

//  unsigned int Hash(Key key);
//  unsigned int Hash(std::string key);

  size_t Hash(Key key);

 private:
  size_t HashNumeric(Key key);
  size_t HashString(std::string key);

  std::vector<bucket> buckets_{};

};

template<typename Key, typename Value>
void HashTable<Key, Value>::print() {
  for (int i = 0; i < buckets_.size(); ++i) {
    std::cout << "bucket - " << i << " {";
    for (auto itr : buckets_[i]) {
      std::cout << " " << itr.first << ":" << itr.second << " ";
    }
    std::cout << "}" << std::endl;
  }
}

}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
