#include "controller.h"

namespace s21 {
CalculatorController::CalculatorController(CalculatorModel* model,
                                           CalculatorView* view,
                                           GraphWidget* graphWidget,
                                           QObject* parent)
    : QObject(parent), model(model), view(view), graphWidget(graphWidget) {
  connect(view, &CalculatorView::buttonClicked, this,
          &CalculatorController::buttonClicked);
  connect(model, &CalculatorModel::inputUpdated, this,
          &CalculatorController::updateView);
  connect(view, &CalculatorView::xValueEntered, this,
          &CalculatorController::xValueEntered);
  connect(view, &CalculatorView::equalsButtonClicked, this,
          &CalculatorController::equalsButtonClicked);
  connect(model, &CalculatorModel::inputError, this,
          &CalculatorController::handleInputError);
  connect(model, &CalculatorModel::calculationResult, this,
          &CalculatorController::handleCalculationResult);
  connect(view, &CalculatorView::drawGraphRequested, this,
          &CalculatorController::handleDrawGraph);
  connect(model, &CalculatorModel::graphDataReady, this,
          &CalculatorController::handleGraphDataReady);
}

void CalculatorController::equalsButtonClicked() {
  double xMin = view->getXMin();
  double xMax = view->getXMax();
  double yMin = view->getYMin();
  double yMax = view->getYMax();
  double step = view->getStep();
  QString xValue = view->getXValue();
  if (xMin > xMax) {
    handleInputError("X Min can not be greater than X Max");
    return;
  }
  if (yMin > yMax) {
    handleInputError("Y Min can not be greater than Y Max");
    return;
  }

  if (step <= 0) {
    handleInputError("Step value should be greater than zero");
    return;
  }
  model->processGraphData(xMin, xMax, yMin, yMax, step);
  model->processX(xValue.toStdString());
  model->processEqualsButton();
}

void CalculatorController::buttonClicked(const QString& buttonValue) {
  model->addInput(buttonValue.toStdString());
}

void CalculatorController::xValueEntered(const QString& value) {
  model->processX(value.toStdString());
}

void CalculatorController::updateView() {
  std::string inputData = model->getInputData();
  QString inputQString = QString::fromStdString(inputData);
  view->updateResultDisplay(inputQString);
}

void CalculatorController::handleInputError(const std::string& errorMessage) {
  QString error = QString::fromStdString(errorMessage);
  view->showError(error);
}

void CalculatorController::handleCalculationResult(const std::string& result) {
  std::cout << "string to convert: " << result << std::endl;
  QString qstr = QString::fromLatin1(result.c_str());
  view->updateResultDisplay(qstr);
}

void CalculatorController::handleDrawGraph(double xMin, double xMax,
                                           double yMin, double yMax,
                                           double step, const QString& xValue) {
  std::vector<double> xValues;  // Create empty vector
  std::vector<double> yValues;  // Create empty vector
  std::string xValueStr = xValue.toStdString();
  model->calculateGraph(xMin, xMax, yMin, yMax, step, xValueStr, xValues,
                        yValues);  // Pass the empty vectors as arguments
}

void CalculatorController::handleGraphDataReady(
    const std::vector<double>& xValues, const std::vector<double>& yValues,
    double yMin, double yMax) {
  QList<double> qXValues;
  for (const auto& value : xValues) {
    qXValues.append(value);
  }

  QList<double> qYValues;
  for (const auto& value : yValues) {
    qYValues.append(value);
  }
  graphWidget->setYRange(yMin, yMax);

  view->setGraphData(qXValues, qYValues, yMin, yMax);
}
}  // namespace s21
