#ifndef CALCMODEL_H
#define CALCMODEL_H

#include <QObject>
#include <iostream>
#include <string>
#include <vector>

#include "s21_parser.h"
#include "s21_validator.h"
namespace s21 {
/**
 * @class
 * @brief Class CalculatorModel - calculator model.
 *
 * The CalculatorModel class represents the calculator model and contains
 * methods for input processing and performing calculations.
 */
class CalculatorModel : public QObject {
  Q_OBJECT
 public:
  /**
   * @brief Constructor for the CalculatorModel class.
   *
   * @param parent The parent object.
   */
  explicit CalculatorModel(QObject* parent = nullptr);

  /**
   * @brief Method for adding input to the model.
   *
   * @param input The input data to add.
   */
  void addInput(const std::string& input);

  /**
   * @brief Method for processing the "=" button press.
   */
  void processEqualsButton();

  /**
   * @brief Method to get the current input data.
   *
   * @return The current input data.
   */
  std::string getInputData() const;

  /**
   * @brief Method for processing the value of variable "x".
   *
   * @param value The value of variable "x".
   */
  void processX(const std::string& value);

  /**
   * @brief Method for processing graph data.
   *
   * @param xMinValue The minimum value of the X-axis.
   * @param xMaxValue The maximum value of the X-axis.
   * @param yMinValue The minimum value of the Y-axis.
   * @param yMaxValue The maximum value of the Y-axis.
   * @param stepValue The step between values on the X-axis.
   */
  void processGraphData(double xMinValue, double xMaxValue, double yMinValue,
                        double yMaxValue, double stepValue);

  /**
   * @brief Method to check if variable "x" is present in the expression.
   *
   * @param inputData The input data to check.
   * @return true if variable "x" is present in the expression, false otherwise.
   */
  bool isXInExpression(const std::string& inputData) const;

  /**
   * @brief Method to calculate graph data.
   *
   * @param xMin The minimum value of the X-axis.
   * @param xMax The maximum value of the X-axis.
   * @param yMin The minimum value of the Y-axis.
   * @param yMax The maximum value of the Y-axis.
   * @param step The step between values on the X-axis.
   * @param xValueStr The value of variable "x" as a string.
   * @param xValues Vector to store the X-axis values.
   * @param yValues Vector to store the Y-axis values.
   */
  void calculateGraph(double xMin, double xMax, double yMin, double yMax,
                      double step, const std::string& xValueStr,
                      std::vector<double>& xValues,
                      std::vector<double>& yValues);

 signals:
  /**
   * @brief Signal emitted when the input data is updated.
   *
   * @param inputData The updated input data.
   */
  void inputUpdated(const std::string& inputData);

  /**
   * @brief Signal emitted when the result is updated.
   *
   * @param result The updated result.
   */
  void resultUpdated(const std::string& result);

  /**
   * @brief Signal emitted when there is an error in the input data.
   *
   * @param errorMessage The error message.
   */
  void inputError(const std::string& errorMessage);

  /**
   * @brief Signal emitted after performing calculations.
   *
   * @param result The calculation result.
   */
  void calculationResult(const std::string& result);

  /**
   * @brief Signal emitted after preparing graph data.
   *
   * @param xValues The X-axis values.
   * @param yValues The Y-axis values.
   * @param yMin The minimum value of the Y-axis.
   * @param yMax The maximum value of the Y-axis.
   */
  void graphDataReady(const std::vector<double>& xValues,
                      const std::vector<double>& yValues, double yMin,
                      double yMax);

  /**
   * @brief Signal emitted when graph data is requested.
   *
   * @param inputData The input data for the graph.
   */
  void graphRequested(const std::string& inputData);

 private:
  double xMin;
  double xMax;
  double yMin;
  double yMax;
  double step;
  std::string inputData;
  std::string xValue;
  Validator validator;
  PolishNotation notation;
};
}  // namespace s21
#endif  // CALCMODEL_H
