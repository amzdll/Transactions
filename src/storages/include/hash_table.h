#ifndef TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
#define TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_

#include <type_traits>

#include "abstract_storage.h"
#include "unordered_map.cc"
#include "unordered_map.h"

namespace s21 {
class HashTable : public AbstractStorage {
 public:
  HashTable() = default;
  ~HashTable() = default;

  bool Set(std::string key, StudentData value, size_t ex = 0) override;
  StudentData Get(std::string key) override;
  bool Exists(std::string key) override;
  bool Del(std::string key) override;
  bool Update(std::string key, StudentData val) override;
  std::vector<std::string> Keys() override;
  bool Rename(std::string old_name, std::string new_name) override;
  //  unsigned int TTL(std::stringkey) override;
  std::vector<std::string> Find(StudentData) override;
  std::vector<StudentData> ShowAll() override;

  //  int Upload(std::string file_path) override;
  //  int Export(std::string file_path) override;

 private:
  s21::unordered_map<std::string, StudentData> hash_table_{};
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
