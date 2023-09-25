#include "s21_validator.h"
namespace s21 {
bool Validator::validate(const std::string& expression) const {
  if (expression.empty()) {
    return false;
  }

  if (expression.length() > 255) {
    return false;
  }

  if (!checkLastCharacter(expression)) {
    return false;
  }

  if (!hasValidParentheses(expression)) {
    return false;
  }

  if (!check_brackets(expression)) {
    return false;
  }

  if (!check_numbers(expression)) {
    return false;
  }

  return true;
}

bool Validator::checkLastCharacter(const std::string& expression) const {
  static const std::regex validLastCharacter("[\\dx\\)]$");
  const std::string lastChar(1, expression.back());
  if (!std::regex_match(lastChar, validLastCharacter)) {
    return false;
  }
  return true;
}

bool Validator::hasValidParentheses(const std::string& expression) const {
  std::vector<std::string> functions = {"cos",  "sin",  "tan", "acos", "asin",
                                        "atan", "sqrt", "ln",  "log"};
  for (const auto& function : functions) {
    size_t pos = expression.find(function);
    while (pos != std::string::npos) {
      if ((pos + function.size()) < expression.size() &&
          expression[pos + function.size()] != '(') {
        std::cerr << "Missing parentheses after function: " << function << "\n";
        return false;
      }
      pos = expression.find(function, pos + function.size());
    }
  }
  return true;
}

bool Validator::check_brackets(const std::string& expression) const {
  std::stack<char> bracketsStack;
  bool lastCharWasClosingBracket = true;

  for (long unsigned int i = 0; i < expression.length(); ++i) {
    const char ch = expression.at(i);
    if (ch == '(') {
      bracketsStack.push(ch);
      lastCharWasClosingBracket = false;
    } else if (ch == ')') {
      if (bracketsStack.empty() || bracketsStack.top() != '(') {
        return false;
      }
      bracketsStack.pop();
      lastCharWasClosingBracket = true;
    }
  }

  return (bracketsStack.empty() && lastCharWasClosingBracket) ||
         bracketsStack.empty();
}

bool Validator::check_numbers(const std::string& expression) const {
  size_t index = 0;
  while (index < expression.length()) {
    if (isdigit(expression[index]) || expression[index] == '.' ||
        expression[index] == 'e') {
      if (!check_and_convert_number(expression, index)) {
        return false;
      }
    } else {
      ++index;
    }
  }
  return true;
}

bool Validator::check_and_convert_number(const std::string& expression,
                                         size_t& index) const {
  std::string number;
  bool hasDecimalPoint = false;
  bool hasExponent = false;
  int decimalPlaces = 0;

  while (index < expression.length() &&
         (isdigit(expression[index]) || expression[index] == '.' ||
          (expression[index] == 'e' || expression[index] == 'E') ||
          (hasExponent &&
           (expression[index] == '+' || expression[index] == '-')))) {
    if (expression[index] == '.') {
      if (hasDecimalPoint) {
        return false;
      }
      hasDecimalPoint = true;
    } else if (hasDecimalPoint) {
      ++decimalPlaces;
    } else if (expression[index] == 'e' || expression[index] == 'E') {
      if (hasExponent) {
        return false;
      }
      hasExponent = true;
    }
    number += expression[index];
    ++index;
  }

  long double value;
  try {
    value = std::stold(number);
  } catch (const std::exception&) {
    return false;
  }

  if (std::fabs(value) > std::numeric_limits<long double>::max()) {
    return false;
  }

  if (decimalPlaces > 7 && !hasExponent) {
    return false;
  }

  return true;
}
}  // namespace s21
