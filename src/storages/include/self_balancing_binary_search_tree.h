#ifndef TRANSACTIONS_SRC_INCLUDE_SELF_BALANCING_BINARY_SEARCH_TREE_H_
#define TRANSACTIONS_SRC_INCLUDE_SELF_BALANCING_BINARY_SEARCH_TREE_H_

#include "abstract_storage.h"
#include "map.cc"
#include "map.h"

namespace s21 {

class SelfBalancingBinarySearchTree : public AbstractStorage {
 public:
  SelfBalancingBinarySearchTree() = default;
  ~SelfBalancingBinarySearchTree() = default;

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
  s21::map<std::string, StudentData> llrb_tree_{};
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_SELF_BALANCING_BINARY_SEARCH_TREE_H_
