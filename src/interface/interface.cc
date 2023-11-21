
#include "interface.h"

namespace s21 {
s21::Interface::Interface() {
  InitCommands();
  int choice = 0;
  std::cout << "Choose data structure:(1 - Hash Table, 2 - Balance Tree)"
            << std::endl;
  std::cin >> choice;
  if (choice == 1) {
    storage_ = new HashTable();
  } else if (choice == 2) {
    ;
  } else {
    std::cout << "Invalid input" << std::endl;
  }
}

void Interface::InitCommands() {
  commands_["Set"] = &Interface::Set;
  commands_["Get"] = &Interface::Get;
  commands_["Exists"] = &Interface::Exists;
  commands_["Del"] = &Interface::Del;
  commands_["Update"] = &Interface::Update;
  commands_["Keys"] = std::bind(&Interface::Keys, this);
  commands_["Rename"] = &Interface::Rename;
  commands_["Find"] = &Interface::Find;
  commands_["ShowAll"] = std::bind(&Interface::ShowAll, this);
}

void Interface::Run() {
  std::string input;
  while (input != "exit") {
    //    std::cout << "Введите команду (или 'exit' для выхода): ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};
    if (!tokens.empty()) {
      auto it = commands_.find(tokens[0]);
      if (it != commands_.end()) {
        tokens.erase(tokens.begin());
        it->second(*this, tokens);
      } else {
        std::cout << "Неизвестная команда." << std::endl;
      }
    }
  }
}

void Interface::Set(const std::vector<std::string> &params) {
  if (params.size() == 6) {
    storage_->Set(params[0], {params});
  }
}

void Interface::Get(const std::vector<std::string> &params) {
  std::cout << "hui2" << std::endl;
}
void Interface::Exists(const std::vector<std::string> &params) {
  std::cout << "hui3" << std::endl;
}
void Interface::Del(const std::vector<std::string> &params) {
  std::cout << "hui4" << std::endl;
}
void Interface::Update(const std::vector<std::string> &params) {
  if (params.size() == 6) {
    storage_->Update(params[0], {params});
  }
}

void Interface::Keys() {
  for (auto key : storage_->Keys()) {
    std::cout << key << std::endl;
  }
}

void Interface::Rename(const std::vector<std::string> &params) {}

void Interface::Find(const std::vector<std::string> &params) {}

void Interface::ShowAll() {
  for (auto value : storage_->ShowAll()) {
    std::printf("%s %s %s %s %s\n", value.name.c_str(), value.surname.c_str(),
                value.city.c_str(), value.year.c_str(), value.coins.c_str());
  }
}

}  // namespace s21
