#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QVector>
#include <QWidget>

class QCustomPlot;

class GraphWidget : public QWidget {
  Q_OBJECT
 public:
  explicit GraphWidget(QWidget* parent = nullptr);
  ~GraphWidget();
  void showGraph(const QVector<double>& xValues,
                 const QVector<double>& yValues);
  void setYRange(double yMin, double yMax);

 private:
  QCustomPlot* plot;
};

#endif  // GRAPHWIDGET_H
