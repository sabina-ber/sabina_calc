#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QGridLayout>
#include <QHash>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QObject>
#include <QPushButton>
#include <QSpinBox>
#include <QValidator>
#include <QVector>
#include <QWidget>

#include "../graph/graphview.h"
namespace s21 {
/**
 * @class CalculatorView
 * @brief The CalculatorView class represents the GUI view for the calculator.
 */
class CalculatorView : public QWidget {
  Q_OBJECT

 public:
  /**
   * @class CalculatorView
   * @brief Constructs a CalculatorView object.
   *
   * @param parent The parent widget.
   */
  CalculatorView(QWidget* parent = nullptr);
  /**
   * @brief Destroys the CalculatorView object and frees any allocated
   * resources.
   */
  ~CalculatorView();
  /**
   * @brief Returns the hash map of buttons.
   *
   * @return The hash map of buttons.
   */
  QHash<QString, QPushButton*> getButtons() const;
  /**
   * @brief Returns the X value entered by the user.
   *
   * @return The X value entered by the user.
   */
  QString getXValue() const;
  void equalsButtonCheck();
  /**
   * @brief Returns the minimum value of X.
   *
   * @return The minimum value of X.
   */
  double getXMin() const;
  /**
   * @brief Returns the maximum value of X.
   *
   * @return The maximum value of X.
   */
  double getXMax() const;
  /**
   * @brief Returns the minimum value of Y.
   *
   * @return The minimum value of Y.
   */
  double getYMin() const;
  /**
   * @brief Returns the maximum value of Y.
   *
   * @return The maximum value of Y.
   */
  double getYMax() const;
  /**
   * @brief Returns the step value entered by the user.
   *
   * @return The step value entered by the user.
   */
  double getStep() const;

 signals:
  void buttonClicked(const QString& buttonValue);
  void equalsButtonClicked();
  void xValueEntered(const QString& value);
  void stepEntered(const QString& stepValue);
  void drawGraphRequested(double xMin, double xMax, double yMin, double yMax,
                          double step, const QString& xValue);

 public slots:
  /**
   * @brief Updates the result display with the provided result.
   *
   * @param result The result to be displayed.
   */
  void updateResultDisplay(const QString& result);
  /**
   * @brief Shows an error message in the result display.
   *
   * @param errorMessage The error message to be displayed.
   */
  void showError(const QString& errorMessage);
  /**
   * @brief Sets the graph data to be displayed.
   *
   * @param xValues The list of X values.
   * @param yValues The list of Y values.
   * @param yMin The minimum Y value.
   * @param yMax The maximum Y value.
   */
  void setGraphData(const QList<double>& xValues, const QList<double>& yValues,
                    double yMin, double yMax);

 private slots:
  /**
   * @brief Handles the button click event.
   */
  void handleButtonClicked();
  /**
   * @brief Handles the X value entered event.
   */
  void handleXValueEntered();
  /**
   * @brief Handles the step entered event.
   */
  void handleStepEntered();
  /**
   * @brief Handles the draw button click event.
   */
  void drawButtonClicked();

 private:
  QHash<QString, QPushButton*> buttons;
  QLineEdit* inputDisplay;
  QLineEdit* inputX;
  QLineEdit* stepInput;
  double xMin;
  double xMax;
  double yMin;
  double yMax;
  QSpinBox* spinBoxXMin;
  QSpinBox* spinBoxXMax;
  QSpinBox* spinBoxYMin;
  QSpinBox* spinBoxYMax;
  QDoubleValidator* numberValidator;
  GraphWidget* graphWidget;
};
}  // namespace s21
#endif  // CALCVIEW_H
