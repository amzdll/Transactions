#ifndef TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_
#define TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_

#include <vector>
#include <string>

namespace s21 {
template <class Key, class Value>
class AbstractStorage {
 public:
  virtual bool Set(Key key, Value value) = 0;
  virtual Value Get(Key key) = 0;
  virtual bool Exists(Key key) = 0;
//  virtual bool Del(Key key) = 0;
//  virtual void Update() = 0;
//  virtual std::vector<std::string> Keys() = 0;
//  virtual void Rename(Key old_name, Key new_name) = 0;
//  virtual unsigned int TTL(Key key) = 0;
//  virtual std::vector<Key> Find(Value) = 0;
//  virtual std::vector<Value> ShowAll() = 0;
//  virtual int Upload(std::string file_path) = 0;
//  virtual int Export(std::string file_path) = 0;

 protected:
 private:
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_ABSTRACT_STORAGE_H_
