#include "student_data.h"

#include <typeinfo>
#include <iostream>

namespace s21 {
StudentData::StudentData()
    : name_({}), surname_({}), year_({}), city_({}), coins_({}) {}

StudentData::StudentData(std::string_view name, std::string_view surname,
                         std::string_view year, std::string_view city,
                         std::string_view coins)
    : name_(name), surname_(surname), year_(year), city_(city), coins_(coins) {}

StudentData::StudentData(const std::vector<std::string>& data) {
  if (data.size() == 5) {
    name_ = data[0];
    surname_ = data[1];
    year_ = data[2];
    city_ = data[3];
    coins_ = data[4];
  }
}

std::string StudentData::ValidateData(const std::vector<std::string>& data) {
  std::cout << "Type of myInt: " << typeid(data[0]).name() << std::endl;
  return std::string();
}

StudentData& StudentData::operator=(const StudentData& other) {
  if (this != &other) {
    if (other.name_ != "-") name_ = other.name_;
    if (other.surname_ != "-") surname_ = other.surname_;
    if (other.city_ != "-") city_ = other.city_;
    if (other.year_ != "-") year_ = other.year_;
    if (other.coins_ != "-") coins_ = other.coins_;
  }
  return *this;
}

bool StudentData::operator==(const StudentData& other) const {
  return (name_ == other.name_ || other.name_ == "-") &&
         (surname_ == other.surname_ || other.surname_ == "-") &&
         (year_ == other.year_ || other.year_ == "-") &&
         (city_ == other.city_ || other.city_ == "-") &&
         (coins_ == other.coins_ || other.coins_ == "-");
}

}  // namespace s21