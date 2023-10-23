#ifndef TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
#define TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_

#include "abstract_storage.h"

#include <vector>
#include <list>

namespace s21 {
template <class Key, class Value>
class HashTable : AbstractStorage<Key, Value> {
 public:
  using bucket = std::list<Value>;

  HashTable();
  ~HashTable();

  bool Set(Value value) override;
  Value Get(Key key) override;
  bool Exists(Key key) override;
  bool Del(Key key) override;
  void Update() override;
  std::vector<std::string> Keys() override;
  void Rename(Key old_name, Key new_name) override;
  unsigned int TTL(Key key) override;
  std::vector<Key> Find(Value) override;
  std::vector<Value> ShowAll() override;
  int Upload(std::string file_path) override;
  int Export(std::string file_path) override;

 private:
  std::vector<bucket> buckets_{};

  int HashFunction();

};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
