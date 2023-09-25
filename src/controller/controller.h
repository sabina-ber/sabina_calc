#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QLocale>
#include <QObject>
#include <QString>
#include <QVector>
#include <vector>

#include "../graph/graphview.h"
#include "../model/calcmodel.h"
#include "../view/calcview.h"

namespace s21 {
/**
 * @class Controller
 * @brief Constructs a CalculatorController object with the given model, view,
 * graphWidget, and parent.
 *
 * @param model The CalculatorModel object.
 * @param view The CalculatorView object.
 * @param graphWidget The GraphWidget object.
 * @param parent The parent QObject.
 */
class CalculatorController : public QObject {
  Q_OBJECT

 public:
  explicit CalculatorController(CalculatorModel* model, CalculatorView* view,
                                GraphWidget* graphWidget,
                                QObject* parent = nullptr);

 public slots:
  /**
   * @brief Handles the equals button click event.
   */
  void equalsButtonClicked();
  /**
   * @brief Handles the button click event.
   *
   * @param buttonValue The value of the clicked button.
   */
  void buttonClicked(const QString& buttonValue);
  /**
   * @brief Handles the X value entered event.
   *
   * @param value The entered X value.
   */
  void xValueEntered(const QString& value);
  /**
   * @brief Handles the draw graph button clicked event.
   *
   * @param xMin The minimum value of X.
   * @param xMax The maximum value of X.
   * @param yMin The minimum value of Y.
   * @param yMax The maximum value of Y.
   * @param step The step value.
   * @param xValue The X value.
   */
  void handleDrawGraph(double xMin, double xMax, double yMin, double yMax,
                       double step, const QString& xValue);

 private slots:
  /**
   * @brief Updates the view with the latest input data from the model.
   */
  void updateView();
  /**
   * @brief Handles an error in the model's input.
   *
   * @param errorMessage The error message.
   */
  void handleInputError(const std::string& errorMessage);
  /**
   * @brief Handles the calculation result from the model.
   *
   * @param result The calculation result.
   */
  void handleCalculationResult(const std::string& result);
  /**
   * @brief Handles the graph data ready event from the model.
   *
   * @param xValues The X values of the graph.
   * @param yValues The Y values of the graph.
   * @param yMin The minimum value of Y.
   * @param yMax The maximum value of Y.
   */
  void handleGraphDataReady(const std::vector<double>& xValues,
                            const std::vector<double>& yValues, double yMin,
                            double yMax);

 private:
  CalculatorModel* model;
  CalculatorView* view;
  GraphWidget* graphWidget;
};
}  // namespace s21
#endif  // CONTROLLER_H
