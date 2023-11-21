#ifndef TRANSACTIONS_SRC_INCLUDE_INFO_SCHOOL_H_
#define TRANSACTIONS_SRC_INCLUDE_INFO_SCHOOL_H_

#include <cstdlib>
#include <string>
#include <vector>

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

  PersonalData(const std::vector<std::string>& data) {
    if (data.size() == 6) {
      name = data[1];
      surname = data[2];
      year = data[3];
      city = data[4];
      coins = data[5];
    }
  }

  PersonalData &operator=(PersonalData const &other) {
    if (this != &other) {
      if (other.name != "-") name = other.name;
      if (other.surname != "-") surname = other.surname;
      if (other.city != "-") city = other.city;
      if (other.year != "-") year = other.year;
      if (other.coins != "-") coins = other.coins;
    }
    return *this;
  }

  bool operator==(const PersonalData &other) const {
    return (name == other.name || other.name == "-") &&
        (surname == other.surname || other.surname == "-") &&
        (year == other.year || other.year == "-") &&
        (city == other.city || other.city == "-") &&
        (coins == other.coins || other.coins == "-");
  }
};
}  // namespace s21

#endif  // TRANSACTIONS_SRC_INCLUDE_INFO_SCHOOL_H_
