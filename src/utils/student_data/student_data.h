#ifndef TRANSACTIONS_SRC_UTILS_STUDENT_DATA_STUDENT_DATA_H_
#define TRANSACTIONS_SRC_UTILS_STUDENT_DATA_STUDENT_DATA_H_

#include <cstdlib>
#include <string>
#include <vector>

namespace s21 {
class StudentData {
 public:
  StudentData();
  StudentData(std::string_view name, std::string_view surname,
              std::string_view year, std::string_view city,
              std::string_view coins);

  StudentData(const std::vector<std::string> &data);
  ~StudentData() = default;

  StudentData &operator=(StudentData const &other);
  bool operator==(const StudentData &other) const;

  std::string ValidateData(const std::vector<std::string>& data);

  std::string get_name() { return name_; };
  std::string get_surname() { return surname_; };
  std::string get_year() { return year_; };
  std::string get_city() { return city_; };
  std::string get_coins() { return coins_; };

 private:
  std::string name_;
  std::string surname_;
  std::string year_;
  std::string city_;
  std::string coins_;
};

}  // namespace s21

#endif  // TRANSACTIONS_SRC_UTILS_STUDENT_DATA_STUDENT_DATA_H_
