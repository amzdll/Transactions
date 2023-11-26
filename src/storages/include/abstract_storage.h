#ifndef TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_
#define TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_

#include <string>
#include <vector>
#include "student_data.h"

namespace s21 {
class AbstractStorage {
 public:
  virtual ~AbstractStorage() = default;

  virtual bool Set(std::string key, StudentData value, size_t ex = 0) = 0;
  virtual StudentData Get(std::string key) = 0;
  virtual bool Exists(std::string key) = 0;
  virtual bool Del(std::string key) = 0;
  virtual bool Update(std::string key, StudentData value) = 0;
  virtual std::vector<std::string> Keys() = 0;
  virtual bool Rename(std::string old_name, std::string new_name) = 0;
  //  virtual unsigned int TTL(std::string key) = 0;
  virtual std::vector<std::string> Find(StudentData) = 0;
  virtual std::vector<StudentData> ShowAll() = 0;

  //  virtual int Upload(std::string file_path) = 0;
  //  virtual int Export(std::string file_path) = 0;
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_
