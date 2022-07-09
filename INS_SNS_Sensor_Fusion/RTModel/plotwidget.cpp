// plotwidget.cpp:
#include "plotwidget.h"

#include "common.h"

#include "qcustomplot.h"

PlotWidget::PlotWidget(QWidget * parent) : QWidget(parent)
  , plot( new QCustomPlot(this) )
{
    setInteractions();
    setGraphs();
    setupLayout();

    plot->xAxis->setLabel(toUni("t, с"));
}

void PlotWidget::addTitle(const QString & title)
{
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title));
}

void PlotWidget::setXRange(const double xMin, const double xMax)
{
    plot->xAxis->setRange(xMin, xMax);
}

void PlotWidget::setYRange(const double yMin, const double yMax)
{
    plot->yAxis->setRange(yMin, yMax);
}

void PlotWidget::addPoint(double x, double y, GraphId Id)
{
    plot->graph( Id )->addData(x, y);
    plot->replot();
}

void PlotWidget::setInteractions()
{
    plot->setInteraction(QCP::iRangeZoom);
    plot->setInteraction(QCP::iRangeDrag);
}

void PlotWidget::setGraphs()
{
    plot->addGraph();
    plot->graph(INS)->setPen(QPen(Qt::magenta));

    plot->addGraph();
    plot->graph(SNS1)->setPen(QPen(Qt::cyan));

    plot->addGraph();
    plot->graph(SNS2)->setPen(QPen(Qt::darkYellow));

    plot->addGraph();
    plot->graph(ESTIMATION)->setPen(QPen(Qt::blue));
//    QPen pen;
//    pen.setWidth(5);
//    pen.setColor(Qt::blue);
//    plot->graph(ESTIMATION)->setPen(pen);

    plot->addGraph();
    plot->graph(REAL)->setPen(QPen(Qt::green));
}

void PlotWidget::setupLayout()
{
    QVBoxLayout * mainLO = new QVBoxLayout;
    mainLO->addWidget( plot );
    setLayout( mainLO );
}
