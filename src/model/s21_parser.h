#ifndef S21_PARSER_H
#define S21_PARSER_H

#include <cmath>
#include <iostream>
#include <list>
#include <locale>
#include <map>
#include <stack>
#include <string>
namespace s21 {
/**
 * @class PolishNotation
 * @brief Processes the input string and evaluates the expression in Polish
 * Notation.
 */
class PolishNotation {
  /// Enumeration of types
  enum TokenType {
    NUMBER,        // число
    PLUS,          // +
    MINUS,         // -
    UNARY,         // ~
    MUL,           // *
    DIV,           // /
    POW,           // ^
    SIN,           // sin
    COS,           // cos
    TAN,           // tan
    ASIN,          // asin
    ACOS,          // acos
    ATAN,          // atan
    SQRT,          // sqrt
    LN,            // ln
    LOG,           // log
    MOD,           // mod
    BRACKET_OPEN,  // (
    BRACKET_CLOSE  // )
  };

  struct Token {
    TokenType type;
    double value;

    Token(TokenType type, double value = 0) : type(type), value(value) {}
  };

 public:
  /**
   * @class PolishNotation
   * @brief Метод для обработки математического выражения.
   *
   * @param input Входное математическое выражение.
   * @return Результат вычислений.
   */
  long double process(std::string input);

 private:
  std::list<Token> tokens;
  static std::map<std::string, TokenType> functionTokenMap();

  /**
   * @class PolishNotation
   * @brief Searches for unary minus in the input string and replaces it with
   * '~'.
   *
   * @param input The input string.
   */
  void search_for_unary_minus(std::string& input);

  /**
   * @class PolishNotation
   * @brief Sorts the input expression into Polish Notation.
   *
   * @param input The input expression string.
   * @param notation The object to store the sorted notation.
   */
  void sort_station(std::string& input, PolishNotation& notation);

  /**
   * @class PolishNotation
   * @brief Checks if a character is an operator.
   *
   * @param c The character to check.
   * @return True if the character is an operator, false otherwise.
   */
  bool isOperator(char c);

  /**
   * @brief Checks if a character is a digit.
   *
   * @param c The character to check.
   * @return True if the character is a digit, false otherwise.
   */
  bool isDigit(char c);

  /**
   * @brief Processes a function and adds it to the stack.
   *
   * @param stack The stack of operators.
   * @param input The input expression string.
   * @param i The current index in the input string.
   */
  void processFunction(std::stack<Token>& stack, const std::string& input,
                       size_t& i);

  /**
   * @brief Processes an operator and adds it to the notation.
   *
   * @param stack The stack of operators.
   * @param notation The object to store the notation.
   * @param c The operator character.
   */
  void processOperator(std::stack<Token>& stack, PolishNotation& notation,
                       char c);

  /**
   * @brief Processes a number and adds it to the notation.
   *
   * @param notation The object to store the notation.
   * @param input The input expression string.
   * @param i The current index in the input string.
   */
  void processNumber(PolishNotation& notation, const std::string& input,
                     size_t& i);

  /**
   * @brief Processes a closing bracket and adds the operators in between to the
   * notation.
   *
   * @param stack The stack of operators.
   * @param polishNotation The object to store the notation.
   */
  void processBracketClose(std::stack<Token>& stack,
                           PolishNotation& polishNotation);

  /**
   * @brief Pushes a token to the notation.
   *
   * @param token The token to push.
   */
  void push(const Token& token);

  /**
   * @brief Checks if a token type is unary.
   *
   * @param type The token type to check.
   * @return True if the token type is unary, false otherwise.
   */
  bool isUnary(TokenType type);

  /**
   * @brief Returns the priority level of an operator token type.
   *
   * @param type The token type to get the priority of.
   * @return The priority level of the operator.
   */
  int operatorPriority(TokenType type);

  /**
   * @brief Performs a unary mathematical operation.
   *
   * @param num The operand.
   * @param type The operator token type.
   * @return The result of the operation.
   */
  long double math_unary(long double num, TokenType type);

  /**
   * @brief Performs a binary mathematical operation.
   *
   * @param num1 The first operand.
   * @param num2 The second operand.
   * @param type The operator token type.
   * @return The result of the operation.
   */
  long double math_binary(long double num1, long double num2, TokenType type);

  /**
   * @brief Calculates the result of the expression in Polish Notation.
   *
   * @param notation The object containing the notation.
   * @return The result of the expression.
   */
  long double calculate(PolishNotation& notation);

  /**
   * @brief Converts a character to its corresponding operator token type.
   *
   * @param c The character to convert.
   * @return The operator token type.
   */
  TokenType charToOperatorToken(char c);
};
}  // namespace s21
#endif  // S21_PARSER_H
