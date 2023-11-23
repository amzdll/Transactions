#include "hash_table.h"

namespace s21 {
bool HashTable::Set(std::string key, StudentData value, size_t ex) {
  return hash_table_.insert({key, value}).second;
}

StudentData HashTable::Get(std::string key) {
  return hash_table_.contains(key) ? hash_table_.find(key)->second
                                   : StudentData();
}

bool HashTable::Exists(std::string key) {
  return hash_table_.find(key) != hash_table_.end();
}

bool HashTable::Del(std::string key) {
  unordered_map<std::string, StudentData>::iterator itr = hash_table_.find(key);
  if (itr != hash_table_.end()) {
    hash_table_.erase(itr);
  }
  return itr != hash_table_.end();
}

bool HashTable::Update(std::string key, StudentData value) {
  if (!hash_table_.contains(key)) {
    return false;
  }
  hash_table_[key] = value;
  return true;
}

std::vector<std::string> HashTable::Keys() {
  std::vector<std::string> keys{};
  for (const auto& itr: hash_table_) {
    keys.push_back(itr.first);
  }
  return keys;
}

std::vector<std::string> HashTable::Find(StudentData value) {
  std::vector<std::string> keys{};
  for (const auto& itr: hash_table_) {
    if (itr.second == value) {
      keys.push_back(itr.first);
    }
  }
  return keys;
}

std::vector<StudentData> HashTable::ShowAll() {
  std::vector<StudentData> values{};
  for (const auto& itr: hash_table_) {
    values.push_back(itr.second);
  }
  return values;
}

bool HashTable::Rename(std::string old_name, std::string new_name) {
  if (!hash_table_.contains(old_name) && hash_table_.contains(new_name)) {
    return false;
  }
  auto iterator = hash_table_.find(old_name);
  hash_table_.erase(iterator);
  hash_table_.insert({new_name, iterator->second});
  return true;
}
}  // namespace s21
