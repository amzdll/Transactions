
#include <bitset>
#include "../include/hash_table.h"

namespace s21 {
bool HashTable::Set(std::string key, PersonalData value, size_t ex) {
  return hash_table_.insert({key, value}).second;
}

PersonalData HashTable::Get(std::string key) {
  return hash_table_.find(key)->second;
}

bool HashTable::Exists(std::string key) {
  return hash_table_.find(key) != hash_table_.end();
}

bool HashTable::Del(std::string key) {
  unordered_map<std::string, PersonalData>::iterator itr = hash_table_.find(key);
  hash_table_.erase(itr);
  return itr != hash_table_.end();
}

void HashTable::Update(std::string key, PersonalData value) {
//  bool is_updated = false;
//  int hash_key = Hash(key);
//  auto pos = buckets_[hash_key].begin();
//  for (; pos != buckets_[hash_key].end() && !is_updated; ++pos) {
//    if (key == pos->first) {
//      is_updated = true;
//      pos->second = value;
//    }
//  }
}

std::vector<std::string> HashTable::Keys() {
  std::vector<std::string> keys{};
  for (auto itr = hash_table_.begin(); itr != hash_table_.end(); ++itr) {
    keys.push_back(itr->first);
  }
  return keys;
}

std::vector<std::string> HashTable::Find(PersonalData value) {
  std::vector<std::string> keys{};
//  for (int i = 0; i < buckets_.size(); ++i) {
//    for (auto itr : buckets_[i]) {
//      if (itr.second == value) {
//        keys.push_back(itr.first);
//      }
//    }
//  }
  return keys;
}

std::vector<PersonalData> HashTable::ShowAll() {
  std::vector<PersonalData> values{};
//  for (int i = 0; i < buckets_.size(); ++i) {
//    for (auto itr : buckets_[i]) {
//      values.push_back(itr.second);
//    }
//  }
  return values;
}

bool HashTable::Rename(std::string old_name, std::string new_name) {
//  bool is_renamed = false;
//  if (!Exists(new_name)) {
//    int hash_key = Hash(old_name);
//    auto pos = buckets_[hash_key].begin();
//    for (; pos != buckets_[hash_key].end() && !is_renamed; ++pos) {
//      if (old_name == pos->first) {
//        is_renamed = true;
//        pos->first = new_name;
//      }
//    }
//  }
  return false;
}
}  // namespace s21



int main() {
  return 0;
}
