#include "self_balancing_binary_search_tree.h"

namespace s21 {
bool SelfBalancingBinarySearchTree::Set(std::string key, StudentData value,
                                        size_t ex) {
  return (llrb_tree_.insert(key, value)).second;
}

StudentData SelfBalancingBinarySearchTree::Get(std::string key) {
  return llrb_tree_.contains(key) ? llrb_tree_.find(key)->second
                                  : StudentData();
}

bool SelfBalancingBinarySearchTree::Exists(std::string key) {
  return llrb_tree_.find(key) != llrb_tree_.end();
}

bool SelfBalancingBinarySearchTree::Del(std::string key) {
  map<std::string, StudentData>::iterator itr = llrb_tree_.find(key);
  if (itr != llrb_tree_.end()) {
    llrb_tree_.erase(itr);
  }
  return itr != llrb_tree_.end();
}

bool SelfBalancingBinarySearchTree::Update(std::string key, StudentData value) {
  if (!llrb_tree_.contains(key)) {
    return false;
  }
  llrb_tree_[key] = value;
  return true;
}

std::vector<std::string> SelfBalancingBinarySearchTree::Keys() {
  std::vector<std::string> keys{};
  for (const auto& itr : llrb_tree_) {
    keys.push_back(itr.first);
  }
  return keys;
}

std::vector<std::string> SelfBalancingBinarySearchTree::Find(
    StudentData value) {
  std::vector<std::string> keys{};
  for (const auto& itr : llrb_tree_) {
    if (itr.second == value) {
      keys.push_back(itr.first);
    }
  }
  return keys;
}

std::vector<StudentData> SelfBalancingBinarySearchTree::ShowAll() {
  std::vector<StudentData> values{};
  for (const auto& itr : llrb_tree_) {
    values.push_back(itr.second);
  }
  return values;
}

bool SelfBalancingBinarySearchTree::Rename(std::string old_name,
                                           std::string new_name) {
  if (!llrb_tree_.contains(old_name) && llrb_tree_.contains(new_name)) {
    return false;
  }
  auto iterator = llrb_tree_.find(old_name);
  StudentData student_data = iterator->second;
  llrb_tree_.erase(iterator);
  llrb_tree_.insert(new_name, student_data);
  return true;
}
}  // namespace s21
