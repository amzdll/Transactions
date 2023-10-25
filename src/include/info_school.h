#ifndef TRANSACTIONS_SRC_INCLUDE_INFO_SCHOOL_H_
#define TRANSACTIONS_SRC_INCLUDE_INFO_SCHOOL_H_

#include <cstdlib>
#include <string>

namespace s21 {
struct PersonalData {
  std::string name;
  std::string surname;
  std::string year;
  std::string city;
  std::string coins;

  PersonalData(std::string_view name, std::string_view surname,
               std::string_view year, std::string_view city,
               std::string_view coins)
      : name(name), surname(surname), year(year), city(city), coins(coins) {}

  PersonalData() : name({}), surname({}), year({}), city({}), coins({}) {}

  void operator=(PersonalData& other) {
    if (other.name != "-") this->name = other.name;
    if (other.surname != "-") this->surname = other.surname;
    if (other.city != "-") this->city = other.city;
    if (other.year != "-") this->year = other.year;
    if (other.coins != "-") this->coins = other.coins;
  }

  bool operator==(const PersonalData& other) const {
    return (name == other.name || other.name == "-") &&
           (surname == other.surname || other.surname == "-") &&
           (year == other.year || other.year == "-") &&
           (city == other.city || other.city == "-") &&
           (coins == other.coins || other.coins == "-");
  }
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_INFO_SCHOOL_H_
