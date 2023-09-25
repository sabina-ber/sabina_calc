#include "calcmodel.h"
namespace s21 {
CalculatorModel::CalculatorModel(QObject* parent)
    : QObject(parent), inputData("") {}

void CalculatorModel::addInput(const std::string& input) {
  std::string clearCommand = "CLEAR";
  std::string delCommand = "DEL";
  if (input == delCommand) {
    if (!inputData.empty()) {
      inputData.pop_back();
    }
  } else if (input == clearCommand) {
    inputData.clear();
    xValue.clear();
  } else {
    inputData += input;
  }
  emit inputUpdated(inputData);
}

bool CalculatorModel::isXInExpression(const std::string& expression) const {
  return expression.find('x') != std::string::npos;
}

void CalculatorModel::processEqualsButton() {
  bool isvalid = validator.validate(inputData);
  if (!isvalid) {
    emit inputError("Error: Invalid input");
    return;
  }
  std::string expression = inputData;

  if (isXInExpression(expression)) {
    if (!xValue.empty()) {
      size_t found = expression.find('x');
      while (found != std::string::npos) {
        expression.replace(found, 1, xValue);
        found = expression.find('x');
      }
      PolishNotation notation;
      try {
        long double result = notation.process(expression);
        emit calculationResult(std::to_string(result));
      } catch (const std::exception& e) {
        emit inputError(e.what());
      }
    } else {
      processGraphData(xMin, xMax, yMin, yMax, step);
      std::vector<double> xValues;
      std::vector<double> yValues;
      calculateGraph(xMin, xMax, yMin, yMax, step, xValue, xValues, yValues);
    }
  } else {
    PolishNotation notation;
    try {
      long double result = notation.process(expression);
      emit calculationResult(std::to_string(result));
    } catch (const std::exception& e) {
      emit inputError(e.what());
    }
  }
}

void CalculatorModel::calculateGraph(double xMin, double xMax, double yMin,
                                     double yMax, double step,
                                     const std::string& xValueStr,
                                     std::vector<double>& xValues,
                                     std::vector<double>& yValues) {
  (void)xValueStr;
  processGraphData(xMin, xMax, yMin, yMax, step);
  if (step == 0.0) {
    emit inputError("Error: Step cannot be zero");
    return;
  }
  bool isvalid = validator.validate(inputData);
  if (!isvalid) {
    emit inputError("Error: Invalid input");
    return;
  }
  int numSteps = static_cast<int>((xMax - xMin) / step);
  for (int i = 0; i <= numSteps; ++i) {
    double x = xMin + i * step;
    std::string expression = inputData;
    size_t found = expression.find('x');
    while (found != std::string::npos) {
      expression.replace(found, 1, std::to_string(x));
      found = expression.find('x');
    }
    PolishNotation notation;
    try {
      long double y = notation.process(expression);
      if (y < yMin || y > yMax) {
        continue;
      }
      xValues.push_back(x);
      yValues.push_back(y);
    } catch (const std::exception& e) {
      emit inputError(e.what());
      break;
    }
  }
  emit graphDataReady(xValues, yValues, yMin, yMax);
}

std::string CalculatorModel::getInputData() const { return inputData; }

void CalculatorModel::processX(const std::string& value) { xValue = value; }

void CalculatorModel::processGraphData(double xMinValue, double xMaxValue,
                                       double yMinValue, double yMaxValue,
                                       double stepValue) {
  xMin = xMinValue;
  xMax = xMaxValue;
  yMin = yMinValue;
  yMax = yMaxValue;
  step = stepValue;
}
}  // namespace s21
