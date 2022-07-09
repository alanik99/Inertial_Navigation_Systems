// mainwidget.cpp:
#include "mainwidget.h"

#include "coordinateswidget.h"
#include "errorswidget.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

MainWidget::MainWidget(Settings * settings, QWidget *parent) : QWidget(parent)
  , settings( settings )
  , tabWidget( new QTabWidget(this) )
  , coordsWidget( new CoordinatesWidget(settings) )
  , errWidget( new ErrorsWidget(settings) )
  , onStr(  toUni("Включить") )
  , offStr( toUni("Выключить") )
  , onStyleSheet("color: green; font-size: 12px; font-weight: bold")
  , offStyleSheet("color: red; font-size: 12px; font-weight: bold")
  , switchSns1Btn( new QPushButton() )
  , switchSns2Btn( new QPushButton() )
{
    connections();
    initButtons();
    initLayout();

    setMinimumSize(1280, 720);
    showMaximized();
}

void MainWidget::addPointsIns(const QVector<double> &points)
{
    coordsWidget->addPointsIns(points);
}

void MainWidget::addPointsErrorIns(const QVector<double> &points)
{
    errWidget->addPointsReal(points);
}

void MainWidget::addPointsSns1(const QVector<double> &points)
{
    coordsWidget->addPointsSns1(points);
}

void MainWidget::addPointsDifferenceWithSns1(const QVector<double> &points)
{
    errWidget->addPointsSns1(points);
}

void MainWidget::addPointsSns2(const QVector<double> &points)
{
    coordsWidget->addPointsSns2(points);
}

void MainWidget::addPointsDifferenceWithSns2(const QVector<double> &points)
{
    errWidget->addPointsSns2(points);
}

void MainWidget::addPointsEstimation(const QVector<double> &points)
{
    coordsWidget->addPointsEstimation(points);
}

void MainWidget::addPointsErrorEstimation(const QVector<double> &points)
{
    errWidget->addPointsEstimation(points);
}

void MainWidget::addPointsReal(const QVector<double> &points)
{
    coordsWidget->addPointsReal(points);
}

void MainWidget::handleBtn1Click()
{
    handleClick( switchSns1Btn, SNS1 );
}

void MainWidget::handleBtn2Click()
{
    handleClick( switchSns2Btn, SNS2 );
}

void MainWidget::connections()
{
    connect( switchSns1Btn, SIGNAL(clicked()),
             this, SLOT(handleBtn1Click()));

    connect( switchSns2Btn, SIGNAL(clicked()),
             this, SLOT(handleBtn2Click()));
}

void MainWidget::initButtons()
{
    switchSns1Btn->setText(offStr);
    switchSns2Btn->setText(offStr);

    switchSns1Btn->setStyleSheet(offStyleSheet);
    switchSns2Btn->setStyleSheet(offStyleSheet);

    switchSns1Btn->setFixedWidth(100);
    switchSns2Btn->setFixedWidth(100);

    switchSns1Btn->setFixedHeight(35);
    switchSns2Btn->setFixedHeight(35);
}

void MainWidget::initLayout()
{
    QVBoxLayout * mainLO = new QVBoxLayout();

    // tabs
    tabWidget->addTab( coordsWidget, toUni("Координаты") );
    tabWidget->addTab( errWidget, toUni("Ошибки") );
    mainLO->addWidget( tabWidget );

    // legend
    QHBoxLayout * bottomLO = new QHBoxLayout();

    QGroupBox * legendBox = new QGroupBox( toUni("Обозначения") );
    legendBox->setFixedHeight(70);
    legendBox->setFont( QFont("Courier New", 10, QFont::Bold) );
    QHBoxLayout * legendBoxLO = new QHBoxLayout();

    QVBoxLayout * legendLO1 = new QVBoxLayout();
    QLabel * real = new QLabel("<font color=#00FF00>\u2014</font>" + toUni("Реальный параметр"));
    QLabel * estimation = new QLabel("<font color=blue>\u2014</font>" + toUni("Оценка"));
    legendLO1->addWidget(real);
    legendLO1->addWidget(estimation);
    legendBoxLO->addLayout(legendLO1);

    QVBoxLayout * legendLO2 = new QVBoxLayout();
    QLabel * sns1 = new QLabel("<font color=cyan>\u2014</font>" + toUni("Измерение СНС1"));
    QLabel * sns2 = new QLabel("<font color=#9b870c>\u2014</font>" + toUni("Измерение СНС2"));
    legendLO2->addWidget(sns1);
    legendLO2->addWidget(sns2);
    legendBoxLO->addLayout(legendLO2);

    QLabel * ins = new QLabel("<font color=#FF00FF>\u2014</font>" + toUni("Измерение ИНС"));
    legendBoxLO->addWidget(ins);
    legendBox->setLayout(legendBoxLO);

    bottomLO->addWidget(legendBox);

    bottomLO->addSpacerItem( new QSpacerItem(100, 20) );

    // buttons
    QGroupBox * sns1Box = new QGroupBox( toUni("СНС1") );
    sns1Box->setFixedHeight(70);
    sns1Box->setFont( QFont("Courier New", 10, QFont::Bold) );
    QHBoxLayout * sns1BoxLO = new QHBoxLayout();
    sns1BoxLO->addWidget( switchSns1Btn );
    sns1Box->setLayout(sns1BoxLO);
    bottomLO->addWidget(sns1Box);

    QGroupBox * sns2Box = new QGroupBox( toUni("СНС2") );
    sns2Box->setFixedHeight(70);
    sns2Box->setFont( QFont("Courier New", 10, QFont::Bold) );
    QHBoxLayout * sns2BoxLO = new QHBoxLayout();
    sns2BoxLO->addWidget( switchSns2Btn );
    sns2Box->setLayout(sns2BoxLO);
    bottomLO->addWidget(sns2Box);

    bottomLO->addStretch();

    mainLO->addLayout( bottomLO );
    setLayout(mainLO);
}

void MainWidget::handleClick(QPushButton *btn, SnsId id)
{
    if      ( btn->text() == QString(offStr) )
    {
        emit switchSns(id, OFF);
        btn->setText(onStr);
        btn->setStyleSheet(onStyleSheet);
    }

    else if ( btn->text() == QString(onStr) )
    {
        emit switchSns(id, ON);
        btn->setText(offStr);
        btn->setStyleSheet(offStyleSheet);
    }
}


