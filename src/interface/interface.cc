#include "interface.h"

namespace s21 {
s21::Interface::Interface() {
  InitCommands();
  InitStorage();
}

bool Interface::InitStorage() {
  int choice = 0;
  bool inited = false;
  std::cout << "Choose data structure:(1 - Hash Table, 2 - Balance Tree)"
            << std::endl;
  std::cin >> choice;
  if (choice == 1) {
    storage_ = new HashTable();
    inited = true;
  } else if (choice == 2) {
    inited = true;
  } else {
    std::cout << "Invalid input" << std::endl;
  }
  return inited;
}

void Interface::InitCommands() {
  commands_["Set"] = &Interface::Set;
  commands_["Get"] = &Interface::Get;
  commands_["Exists"] = &Interface::Exists;
  commands_["Del"] = &Interface::Del;
  commands_["Update"] = &Interface::Update;
  commands_["Rename"] = &Interface::Rename;
  commands_["Find"] = &Interface::Find;
  commands_["Keys"] = std::bind(&Interface::Keys, this);
  commands_["ShowAll"] = std::bind(&Interface::ShowAll, this);
}

void Interface::Run() {
  std::string input;
  while (input != "exit") {
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
    if (storage_->Set(params[0], {params})) {
      std::cout << "> OK" << std::endl;
    } else {
      ;
    }
  }
}

void Interface::Get(const std::vector<std::string> &params) {
  if (params.size() == 1) {
    PersonalData personal_data = storage_->Get(params[0]);
    //    if (!personal_data.empty())
    //    else std::cout << "> (null)" << std::endl;
    std::printf("> %s %s %s %s %s\n", personal_data.name.c_str(),
                personal_data.surname.c_str(), personal_data.city.c_str(),
                personal_data.year.c_str(), personal_data.coins.c_str());
  }
}

void Interface::Exists(const std::vector<std::string> &params) {
  if (params.size() == 1) {
    std::cout << std::boolalpha << "> " << storage_->Exists(params[0])
              << std::endl;
  }
}

void Interface::Del(const std::vector<std::string> &params) {
  if (params.size() == 1) {
    std::cout << std::boolalpha << "> " << storage_->Del(params[0])
              << std::endl;
  }
}

void Interface::Update(const std::vector<std::string> &params) {
  if (params.size() == 6) {
    storage_->Update(params[0], {params});
  }
}

void Interface::Keys() {
  int counter = 1;
  for (const auto &key : storage_->Keys()) {
    std::cout << counter << ") " << key << std::endl;
    ++counter;
  }
}

void Interface::Rename(const std::vector<std::string> &params) {
  if (params.size() == 2) {
    storage_->Rename(params[0], params[1]);
  }
}

void Interface::Find(const std::vector<std::string> &params) {}

void Interface::ShowAll() {
  for (auto value : storage_->ShowAll()) {
    std::printf("%s %s %s %s %s\n", value.name.c_str(), value.surname.c_str(),
                value.city.c_str(), value.year.c_str(), value.coins.c_str());
  }
}

}  // namespace s21
