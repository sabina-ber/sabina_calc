#include <QApplication>

#include "controller/controller.h"
#include "graph/graphview.h"
#include "model/calcmodel.h"
#include "view/calcview.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::CalculatorModel model;
  s21::CalculatorView view;
  GraphWidget graphWidget;
  s21::CalculatorController controller(&model, &view, &graphWidget);

  view.show();
  return app.exec();
}
