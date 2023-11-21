#ifndef TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_
#define TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_

#include <vector>
#include <string>

#include "info_school.h"

namespace s21 {class AbstractStorage {
 public:
  virtual bool Set(std::string key, PersonalData value, size_t ex = 0) = 0;
  virtual PersonalData Get(std::string key) = 0;
  virtual bool Exists(std::string key) = 0;
  virtual bool Del(std::string key) = 0;
  virtual bool Update(std::string key, PersonalData value) = 0;
  virtual std::vector<std::string> Keys() = 0;
  virtual bool Rename(std::string old_name, std::string new_name) = 0;
//  virtual unsigned int TTL(std::string key) = 0;
  virtual std::vector<std::string> Find(PersonalData) = 0;
  virtual std::vector<PersonalData> ShowAll() = 0;

//  virtual int Upload(std::string file_path) = 0;
//  virtual int Export(std::string file_path) = 0;
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_
