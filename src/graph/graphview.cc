#include "graphview.h"

#include "qcustomplot/qcustomplot.h"

GraphWidget::GraphWidget(QWidget* parent) : QWidget(parent, Qt::Window) {
  plot = new QCustomPlot(this);

  plot->setMinimumSize(450, 450);
  plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GraphWidget::~GraphWidget() { delete plot; }

void GraphWidget::showGraph(const QVector<double>& xValues,
                            const QVector<double>& yValues) {
  plot->addGraph();
  plot->graph(0)->setData(xValues, yValues);
  plot->rescaleAxes();
  plot->replot();
  show();
}

void GraphWidget::setYRange(double yMin, double yMax) {
  plot->yAxis->setRange(yMin, yMax);
  plot->replot();
}
