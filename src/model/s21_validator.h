#ifndef S21_VALIDATOR_H
#define S21_VALIDATOR_H

#include <cctype>
#include <cmath>
#include <iostream>
#include <limits>
#include <regex>
#include <stack>
#include <string>
#include <vector>
namespace s21 {
/**
 * @class Validator
 * @brief Class Validator - validation of a mathematical expression.
 *
 * The Validator class provides functionality to validate a mathematical
 * expression.
 */
class Validator {
 public:
  /**
   * @brief Method to validate a mathematical expression.
   *
   * @param expression The mathematical expression to validate.
   * @return True if the expression is valid, otherwise False.
   */
  bool validate(const std::string& expression) const;

  /**
   * @brief Method to check the last character of a mathematical expression.
   *
   * @param expression The mathematical expression.
   * @return True if the last character is valid, otherwise False.
   */
  bool checkLastCharacter(const std::string& expression) const;

  /**
   * @brief Method to check for the presence of functions in a mathematical
   * expression.
   *
   * @param expression The mathematical expression.
   * @return True if the expression contains functions, otherwise False.
   */
  bool check_functions(const std::string& expression) const;

  /**
   * @brief Method to check parentheses in a mathematical expression.
   *
   * @param expression The mathematical expression.
   * @return True if the parentheses in the expression are valid, otherwise
   * False.
   */
  bool check_brackets(const std::string& expression) const;

  /**
   * @brief Method to check parentheses around functions in a mathematical
   * expression.
   *
   * @param expression The mathematical expression.
   * @return True if the parentheses around functions in the expression are
   * valid, otherwise False.
   */
  bool check_br_for_func(const std::string& expression) const;

  /**
   * @brief Method to check numbers in a mathematical expression.
   *
   * @param expression The mathematical expression.
   * @return True if the numbers in the expression are valid, otherwise False.
   */
  bool check_numbers(const std::string& expression) const;

  /**
   * @brief Method to check the validity of a number.
   *
   * @param number The string representation of the number.
   * @return True if the number is valid, otherwise False.
   */
  bool isValidNum(const std::string& number) const;

  /**
   * @brief Method to check the validity of parentheses in a mathematical
   * expression.
   *
   * @param expression The mathematical expression.
   * @return True if the parentheses in the expression are valid, otherwise
   * False.
   */
  bool hasValidParentheses(const std::string& expression) const;

  /**
   * @brief Method to check and convert a number in a mathematical expression.
   *
   * @param expression The mathematical expression.
   * @param index The index of the number character.
   * @return True if the number is valid and successfully converted, otherwise
   * False.
   */
  bool check_and_convert_number(const std::string& expression,
                                size_t& index) const;

  /**
   * @brief Method to check the presence of an exponent in a mathematical
   * expression.
   *
   * @param expression The mathematical expression.
   * @return True if the exponent in the expression is valid, otherwise False.
   */
  bool check_exponential(const std::string& expression) const;
};
}  // namespace s21
#endif  // S21_VALIDATOR_H
