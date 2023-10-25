#ifndef TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
#define TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
#include "iostream"

#include "abstract_storage.h"
#include "info_school.h"

#include <type_traits>

#include <vector>
#include <list>

namespace s21 {
template<typename Key, typename Value>
class HashTable : AbstractStorage<Key, Value> {
 public:
  using bucket = std::list<std::pair<Key, Value>>;

  HashTable();
  ~HashTable() = default;

  bool Set(Key key, Value value) override;
  Value Get(Key key) override;
  bool Exists(Key key) override;
  bool Del(Key key) override;
  void Update(Key key, Value vale) override;
  std::vector<Key> Keys() override;
  bool Rename(Key old_name, Key new_name) override;
//  unsigned int TTL(Key key) override;
  std::vector<Key> Find(Value) override;
  std::vector<Value> ShowAll() override;

//  int Upload(std::string file_path) override;
//  int Export(std::string file_path) override;


  size_t Hash(Key key);

 private:
  std::vector<bucket> buckets_{};

  size_t HashNumeric(Key key);
  size_t HashString(std::string key);
};

}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
