
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

bool HashTable::Update(std::string key, PersonalData value) {
  if (!hash_table_.contains(key)) {
    return false;
  }
  hash_table_[key] = value;
  return true;
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
  for (auto itr = hash_table_.begin(); itr != hash_table_.end(); ++itr) {
    values.push_back(itr->second);
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

//int main() {
//  s21::HashTable a;
//  a.Set("1", {"1","1","1","1","1"});
//  a.Set("2", {"1","1","1","1","1"});
//  a.Set("3", {"1","1","1","1","1"});
//
//
//  for (const auto& value : a.ShowAll()) {
//    std::cout << value.name << std::endl;
//    std::printf("%s %s %s %s %s\n", value.name.c_str(), value.name.c_str(),
//                value.name.c_str(), value.name.c_str(), value.name.c_str());
//  }
////  for (auto i : a) {
////    std::cout << i.first<< " " << i.second << std::endl;
////  }
//}