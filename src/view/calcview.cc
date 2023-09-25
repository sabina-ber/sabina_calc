#include "calcview.h"
namespace s21 {

CalculatorView::CalculatorView(QWidget* parent)
    : QWidget(parent),
      buttons(),
      inputDisplay(new QLineEdit(this)),
      inputX(new QLineEdit(this)),
      stepInput(new QLineEdit(this)),
      spinBoxXMin(new QSpinBox(this)),
      spinBoxXMax(new QSpinBox(this)),
      spinBoxYMin(new QSpinBox(this)),
      spinBoxYMax(new QSpinBox(this)),
      numberValidator(new QDoubleValidator(this)),
      graphWidget(new GraphWidget(this)) {
  // Set the style for the buttons
  QString buttonStyle =
      "QPushButton {"
      "   background-color: gold;"
      "   border: 1px solid gold;"
      "   color: navy;"
      "   padding: 1px;"
      "   margin: 1px;"
      "   font-size: 12px;"
      "   border-radius: 14px;"
      "}"
      "QPushButton:hover {"
      "   background-color: royalblue;"
      "   border-color: royalblue;"
      "   color: white;"
      "}";
  // Define the labels for the buttons
  QStringList buttonLabels = {
      "0",   "1",    "2",   "3",     "4",    "5",    "6",   "7",    "8",
      "9",   "+",    "-",   "*",     "/",    "log",  "ln",  "cos",  "acos",
      "tan", "atan", "%",   "(",     ")",    ".",    "sin", "asin", "^",
      "x",   "=",    "DEL", "CLEAR", "DRAW", "sqrt", "e"};
  // Create buttons and store them in the hash map
  for (const auto& label : buttonLabels) {
    QPushButton* button = new QPushButton(label, this);
    button->setStyleSheet(buttonStyle);
    button->setFixedSize(67, 67);
    buttons[label] = button;
  }
  // Set the input display as read-only
  inputDisplay->setReadOnly(true);
  // Create the grid layout
  QGridLayout* gridLayout = new QGridLayout(this);
  gridLayout->setSpacing(10);

  // Add buttons to the layout
  gridLayout->addWidget(buttons["1"], 1, 0);
  gridLayout->addWidget(buttons["2"], 1, 1);
  gridLayout->addWidget(buttons["3"], 1, 2);
  gridLayout->addWidget(buttons["4"], 2, 0);
  gridLayout->addWidget(buttons["5"], 2, 1);
  gridLayout->addWidget(buttons["6"], 2, 2);
  gridLayout->addWidget(buttons["7"], 3, 0);
  gridLayout->addWidget(buttons["8"], 3, 1);
  gridLayout->addWidget(buttons["9"], 3, 2);
  gridLayout->addWidget(buttons["0"], 4, 0);
  gridLayout->addWidget(buttons["+"], 5, 3);
  gridLayout->addWidget(buttons["-"], 1, 3);
  gridLayout->addWidget(buttons["*"], 2, 3);
  gridLayout->addWidget(buttons["/"], 3, 3);
  gridLayout->addWidget(buttons["^"], 4, 3);
  gridLayout->addWidget(buttons["log"], 1, 4);
  gridLayout->addWidget(buttons["ln"], 2, 4);
  gridLayout->addWidget(buttons["%"], 2, 5);
  gridLayout->addWidget(buttons["."], 4, 2);
  gridLayout->addWidget(buttons["("], 5, 0);
  gridLayout->addWidget(buttons[")"], 5, 1);
  gridLayout->addWidget(buttons["x"], 4, 1);
  gridLayout->addWidget(buttons["cos"], 5, 4);
  gridLayout->addWidget(buttons["acos"], 5, 5);
  gridLayout->addWidget(buttons["sin"], 4, 4);
  gridLayout->addWidget(buttons["asin"], 4, 5);
  gridLayout->addWidget(buttons["tan"], 3, 4);
  gridLayout->addWidget(buttons["atan"], 3, 5);
  gridLayout->addWidget(buttons["sqrt"], 1, 5);
  gridLayout->addWidget(buttons["="], 5, 2);
  gridLayout->addWidget(buttons["e"], 9, 2);
  gridLayout->addWidget(buttons["DEL"], 9, 3);
  gridLayout->addWidget(buttons["CLEAR"], 9, 4);
  gridLayout->addWidget(buttons["DRAW"], 9, 5);
  // Add input display to the layout
  gridLayout->addWidget(inputDisplay, 0, 0, 1, 6);
  // Add other widgets and labels to the layout
  gridLayout->addWidget(new QLabel("Min X:"), 6, 0);
  gridLayout->addWidget(spinBoxXMin, 6, 1);
  gridLayout->addWidget(new QLabel("Max X:"), 6, 3);
  gridLayout->addWidget(spinBoxXMax, 6, 4);

  gridLayout->addWidget(new QLabel("Min Y:"), 7, 0);
  gridLayout->addWidget(spinBoxYMin, 7, 1);
  gridLayout->addWidget(new QLabel("Max Y:"), 7, 3);
  gridLayout->addWidget(spinBoxYMax, 7, 4);

  inputX->setValidator(numberValidator);

  spinBoxXMin->setMinimum(-1000000);
  spinBoxXMin->setMaximum(1000000);
  spinBoxXMax->setMinimum(-1000000);
  spinBoxXMax->setMaximum(1000000);
  spinBoxYMin->setMinimum(-1000000);
  spinBoxYMax->setMinimum(-1000000);
  spinBoxYMin->setMaximum(1000000);
  spinBoxYMax->setMaximum(1000000);

  spinBoxXMin->setValue(-10);
  spinBoxXMax->setValue(10);
  spinBoxYMin->setValue(-10);
  spinBoxYMax->setValue(10);
  stepInput->setText("0.1");

  // Display layout

  gridLayout->addWidget(new QLabel("X:"), 8, 0);

  inputX->setPlaceholderText("Insert X");
  gridLayout->addWidget(inputX, 8, 1, 1, 1);

  QRegularExpressionValidator* numberValidator =
      new QRegularExpressionValidator(QRegularExpression("-?\\d*\\.?\\d+"),
                                      this);
  inputX->setValidator(numberValidator);

  stepInput->setPlaceholderText("Insert step");
  stepInput->setValidator(numberValidator);
  gridLayout->addWidget(new QLabel("Step:"), 9, 0);
  gridLayout->addWidget(stepInput, 9, 1, 1, 1);
  setLayout(gridLayout);
  // Connect button signals to slots
  for (auto& button : buttons) {
    if ((button->text() != "=") && (button->text() != "DRAW")) {
      connect(button, &QPushButton::clicked, this,
              &CalculatorView::handleButtonClicked);
    }
  }
  connect(inputX, &QLineEdit::returnPressed, this,
          &CalculatorView::handleXValueEntered);
  connect(buttons["="], &QPushButton::clicked, this,
          &CalculatorView::equalsButtonClicked);
  connect(stepInput, &QLineEdit::returnPressed, this,
          &CalculatorView::handleStepEntered);
  connect(buttons["DRAW"], &QPushButton::clicked, this,
          &CalculatorView::drawButtonClicked);
}

CalculatorView::~CalculatorView() {
  // Clean up resources and delete objects
  delete inputDisplay;
  delete inputX;
  delete stepInput;
  delete numberValidator;
  delete spinBoxXMin;
  delete spinBoxXMax;
  delete spinBoxYMin;
  delete spinBoxYMax;
  delete graphWidget;

  for (auto& button : buttons) {
    delete button;
  }
}

QHash<QString, QPushButton*> CalculatorView::getButtons() const {
  return buttons;
}

void CalculatorView::handleButtonClicked() {
  QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
  if (clickedButton) {
    QString buttonValue = clickedButton->text();
    emit buttonClicked(buttonValue);
  }
}

void CalculatorView::handleXValueEntered() {
  QString xValue = inputX->text();
  emit xValueEntered(xValue);
}

void CalculatorView::handleStepEntered() {
  QString stepValue = stepInput->text();
  emit stepEntered(stepValue);
}

void CalculatorView::updateResultDisplay(const QString& result) {
  inputDisplay->setText(result);
}

void CalculatorView::showError(const QString& errorMessage) {
  inputDisplay->setText(errorMessage);
}

void CalculatorView::drawButtonClicked() {
  double xMin = getXMin();
  double xMax = getXMax();
  if (xMin > xMax) {
    showError("X Min can not be greater than X Max");
    return;
  }
  double yMin = getYMin();
  double yMax = getYMax();
  if (yMin > yMax) {
    showError("Y Min can not be greater than Y Max");
    return;
  }
  double step = getStep();
  QString xValue = getXValue();

  emit drawGraphRequested(xMin, xMax, yMin, yMax, step, xValue);
}

void CalculatorView::setGraphData(const QList<double>& xValues,
                                  const QList<double>& yValues, double yMin,
                                  double yMax) {
  QVector<double> qXValues = QVector<double>::fromList(xValues);
  QVector<double> qYValues = QVector<double>::fromList(yValues);
  graphWidget->showGraph(qXValues, qYValues);
  graphWidget->setYRange(yMin, yMax);
}

QString CalculatorView::getXValue() const { return inputX->text(); }

double CalculatorView::getXMin() const { return spinBoxXMin->value(); }

double CalculatorView::getXMax() const { return spinBoxXMax->value(); }

double CalculatorView::getYMin() const { return spinBoxYMin->value(); }

double CalculatorView::getYMax() const { return spinBoxYMax->value(); }

double CalculatorView::getStep() const { return stepInput->text().toDouble(); }
}  // namespace s21
