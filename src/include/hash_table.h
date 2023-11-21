#ifndef TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
#define TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_

#include <type_traits>

#include "../utils/unordered_map/unordered_map.cc"
#include "../utils/unordered_map/unordered_map.h"
#include "abstract_storage.h"
#include "info_school.h"

namespace s21 {
class HashTable : public AbstractStorage {
 public:
  HashTable() = default;
  ~HashTable() = default;

  bool Set(std::string key, PersonalData value, size_t ex = 0) override;
  PersonalData Get(std::string key) override;
  bool Exists(std::string key) override;
  bool Del(std::string key) override;
  bool Update(std::string key, PersonalData val) override;
  std::vector<std::string> Keys() override;
  bool Rename(std::string old_name, std::string new_name) override;
  //  unsigned int TTL(std::stringkey) override;
  std::vector<std::string> Find(PersonalData) override;
  std::vector<PersonalData> ShowAll() override;

  //  int Upload(std::string file_path) override;
  //  int Export(std::string file_path) override;


 private:
  s21::unordered_map<std::string, PersonalData> hash_table_{};
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_HASH_TABLE_H_
