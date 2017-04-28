#ifndef INTERFACE_H
#define INTERFACE_H
#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QStackedBarSeries>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

QT_CHARTS_USE_NAMESPACE

class Interface:public QWidget{
    Q_OBJECT
private:
    QTabWidget *tabWidget;
    QVBoxLayout *mainLayout;
    QLineSeries *graphSeries;
    QChart *graphChart,*histogramChart;
    QChartView *graphChartView, *histogramChartView;
    QBarSet *set;
    QStringList categories;
    QBarCategoryAxis *axis;
    QStackedBarSeries *histogramSeries;
    QPushButton *connectButton, *resetButton;
    QHBoxLayout *horizontalLayout, *lowerLayout;
    QLabel *ipLabel, *portLabel, *label;
    QLineEdit *ipLine, *portLine;
public:
    Interface();
    ~Interface();
    void plotGraph(QList<double> &data);
    void plotHistogram(QList<double> &data);
    QString getIp();
    QString getPort();
private slots:
    void blockLineEdit();
signals:
    void signalFromResetButton();
    void signalFromConnectButton();
};
#endif // INTERFACE_H
