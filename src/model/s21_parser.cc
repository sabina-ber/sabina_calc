#include "s21_parser.h"
namespace s21 {
long double PolishNotation::process(std::string input) {
  PolishNotation notation;
  sort_station(input, notation);
  long double result = calculate(notation);
  return result;
}

void PolishNotation::sort_station(std::string& input,
                                  PolishNotation& notation) {
  std::stack<Token> stack;
  search_for_unary_minus(input);

  for (size_t i = 0; i < input.size(); ++i) {
    char c = input[i];
    if (isDigit(c) || (std::string("еe").find(input[i]) != std::string::npos)) {
      processNumber(notation, input, i);
      if (!stack.empty()) {
        Token topToken = stack.top();
        PolishNotation::TokenType topTokenType = topToken.type;
        if (isUnary(topTokenType)) {
          notation.push(topToken);
          stack.pop();
        }
      }
      i--;
      continue;
    }
    if (std::isalpha(c) &&
        !(std::string("еe").find(input[i]) != std::string::npos)) {
      processFunction(stack, input, i);
      --i;
      continue;
    }
    if (c == '(') {
      stack.push(Token(BRACKET_OPEN));
      continue;
    }
    if (isOperator(c)) {
      processOperator(stack, notation, c);
      continue;
    }
    if (c == ')') {
      processBracketClose(stack, notation);
      continue;
    }
  }

  while (!stack.empty()) {
    notation.push(stack.top());
    stack.pop();
  }
}

bool PolishNotation::isOperator(char c) {
  return std::string("~+-*%/^").find(c) != std::string::npos;
}

bool PolishNotation::isDigit(char c) {
  return std::isdigit(c) || c == '.' || c == ',';
}

void PolishNotation::processOperator(std::stack<Token>& stack,
                                     PolishNotation& notation, char c) {
  TokenType tokenType = charToOperatorToken(c);
  int current = operatorPriority(tokenType);

  while (!stack.empty()) {
    int prev = operatorPriority(stack.top().type);
    if ((current < prev) || ((current == prev) && (tokenType != POW))) {
      notation.push(stack.top());
      stack.pop();
    } else {
      break;
    }
  }
  stack.push(Token(tokenType, 0));
}

void PolishNotation::processNumber(PolishNotation& notation,
                                   const std::string& input, size_t& i) {
  std::string number;
  while (i < input.size() && isDigit(input[i])) {
    number += input[i];
    ++i;
  }
  if (i < input.size() &&
      (std::string("еe").find(input[i]) != std::string::npos)) {
    number += input[i];
    ++i;
    if (i < input.size() && (input[i] == '+' || input[i] == '-')) {
      char exponentSign = input[i];
      ++i;
      if (i < input.size() && std::isdigit(input[i])) {
        number += exponentSign;
      } else {
        --i;
        notation.push(Token(NUMBER, std::stold(number)));
        return;
      }
    }
    while (i < input.size() && isDigit(input[i])) {
      number += input[i];
      ++i;
    }
  }

  notation.push(Token(NUMBER, std::stold(number)));
}

void PolishNotation::search_for_unary_minus(std::string& validated_input) {
  for (size_t i = 0; i < validated_input.size(); i++) {
    if (validated_input[i] == '-' && (i == 0 || validated_input[i - 1] == '(' ||
                                      isOperator(validated_input[i - 1]))) {
      validated_input[i] = '~';
    }
  }
}

void PolishNotation::processFunction(std::stack<Token>& stack,
                                     const std::string& input, size_t& i) {
  std::string funcName;
  while (i < input.size() && std::isalpha(input[i])) {
    funcName += input[i];
    ++i;
  }

  auto funcs = PolishNotation::functionTokenMap();
  if (funcs.count(funcName) > 0) {
    stack.push(Token(funcs[funcName]));
  } else {
    throw std::runtime_error("Unknown function: " + funcName);
  }
}

std::map<std::string, PolishNotation::TokenType>
PolishNotation::functionTokenMap() {
  return {
      {"cos", COS},   {"sin", SIN},   {"tan", TAN},   {"acos", ACOS},
      {"asin", ASIN}, {"atan", ATAN}, {"sqrt", SQRT}, {"ln", LN},
      {"log", LOG},   {"%", MOD},
  };
}

void PolishNotation::processBracketClose(std::stack<Token>& stack,
                                         PolishNotation& polishNotation) {
  while (stack.top().type != BRACKET_OPEN) {
    if (!stack.empty()) {
      polishNotation.push(stack.top());
      stack.pop();
    }
  }
  stack.pop();
}

void PolishNotation::push(const Token& token) { tokens.push_back(token); }

bool PolishNotation::isUnary(TokenType type) {
  switch (type) {
    case ASIN:
    case SIN:
    case COS:
    case ACOS:
    case TAN:
    case ATAN:
    case LOG:
    case LN:
    case UNARY:
    case SQRT:
      return true;
    default:
      return false;
  }
}

int PolishNotation::operatorPriority(TokenType type) {
  switch (type) {
    case POW:
      return 3;
    case UNARY:
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
    case SQRT:
    case LN:
    case LOG:
      return 4;
    case MUL:
    case DIV:
      return 2;
    case PLUS:
    case MINUS:
      return 1;
    case MOD:
      return 2;
    case BRACKET_OPEN:
    case BRACKET_CLOSE:
      return 0;
    default:
      throw std::runtime_error("Unknown operator");
  }
}

PolishNotation::TokenType PolishNotation::charToOperatorToken(char c) {
  switch (c) {
    case '+':
      return PLUS;
    case '-':
      return MINUS;
    case '*':
      return MUL;
    case '/':
      return DIV;
    case '~':
      return UNARY;
    case '^':
      return POW;
    case '%':
      return MOD;
    default:
      throw std::runtime_error("Unknown operator");
  }
}

long

    double
    PolishNotation::math_binary(long double num1, long double num2,
                                TokenType type) {
  long double result = 0.0;
  switch (type) {
    case PLUS:
      result = num2 + num1;
      break;
    case MINUS:
      result = num2 - num1;
      break;
    case MUL:
      result = num2 * num1;
      break;
    case DIV:
      result = num2 / num1;
      break;
    case MOD:
      result = fmod(num2, num1);
      break;
    case POW:
      result = pow(num2, num1);
      break;
    default:
      throw std::invalid_argument("Invalid operator");
  }
  return result;
}

long double PolishNotation::math_unary(long double num, TokenType type) {
  long double result = 0.0;
  switch (type) {
    case UNARY:
      result = num * -1;
      break;
    case SIN:
      result = sin(num);
      break;
    case COS:
      result = cos(num);
      break;
    case TAN:
      result = tan(num);
      break;
    case ACOS:
      result = acos(num);
      break;
    case ASIN:
      result = asin(num);
      break;
    case ATAN:
      result = atan(num);
      break;
    case SQRT:
      result = sqrt(num);
      break;
    case LN:
      result = log(num);
      break;
    case LOG:
      result = log10(num);
      break;
    default:
      throw std::invalid_argument("Invalid function");
  }
  return result;
}

long double PolishNotation::calculate(PolishNotation& notation) {
  std::stack<long double> calcStack;

  for (std::list<Token>::iterator it = notation.tokens.begin();
       it != notation.tokens.end(); ++it) {
    if (it->type == NUMBER) {
      calcStack.push(it->value);
    } else if (isUnary(it->type)) {
      if (calcStack.empty()) {
        throw std::runtime_error("Invalid expression");
      }
      long double num = calcStack.top();
      calcStack.pop();
      calcStack.push(math_unary(num, it->type));
    } else {
      if (calcStack.size() < 2) {
        throw std::runtime_error("Invalid expression");
      }
      long double num2 = calcStack.top();
      calcStack.pop();
      if (calcStack.empty()) {
        throw std::runtime_error("Invalid expression");
      }
      long double num1 = calcStack.top();
      calcStack.pop();
      calcStack.push(math_binary(num2, num1, it->type));
    }
  }

  if (calcStack.size() != 1) {
    throw std::runtime_error("Invalid expression");
  }

  return calcStack.top();
}
}  // namespace s21
