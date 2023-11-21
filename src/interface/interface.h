#ifndef TRANSACTIONS_SRC_INTERFACE_INTERFACE_H_
#define TRANSACTIONS_SRC_INTERFACE_INTERFACE_H_

#include <functional>
#include <iterator>  // Include the <iterator> header
#include <map>
#include <sstream>

#include "../include/hash_table.h"
#include "string"
#include "string_view"

namespace s21 {
class Interface {
 public:
  Interface();
  void Run();

 private:
  void InitCommands();

  void Set(const std::vector<std::string> &params);
  void Get(const std::vector<std::string> &params);
  void Exists(const std::vector<std::string> &params);
  void Del(const std::vector<std::string> &params);
  void Update(const std::vector<std::string> &params);
  void Keys();
  void Rename(const std::vector<std::string> &params);
  void Find(const std::vector<std::string> &params);
  void ShowAll();

  AbstractStorage *storage_;
  std::map<std::string,
           std::function<void(Interface &, const std::vector<std::string> &)>>
      commands_;
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INTERFACE_INTERFACE_H_
