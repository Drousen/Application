#include "interface.h"
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QDebug>
#include <unistd.h>

QT_CHARTS_USE_NAMESPACE

Interface::Interface(){  
    resize(1000, 600);
    tabWidget = new QTabWidget;

    ipLabel = new QLabel("ip:",this);
    ipLine = new QLineEdit("127.0.0.1",this);
    label = new QLabel("",this);
    portLabel = new QLabel("port:",this);
    portLine = new QLineEdit("1234",this);
    connectButton = new QPushButton("Connect",this);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(ipLabel);
    horizontalLayout->addWidget(ipLine);
    horizontalLayout->addWidget(portLabel);
    horizontalLayout->addWidget(portLine);
    horizontalLayout->addWidget(label,1);
    horizontalLayout->addWidget(connectButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(tabWidget);

    lowerLayout = new QHBoxLayout;
    resetButton = new QPushButton("Reset",this);
    lowerLayout->addWidget(label,1);
    lowerLayout->addWidget(resetButton);

    mainLayout->addLayout(lowerLayout);
    setLayout(mainLayout);

    graphSeries = new QLineSeries();
    graphChart = new QChart();
    graphChart->addSeries(graphSeries);
    graphChart->createDefaultAxes();
    graphChart->setTitle("Graph");
    graphChart->legend()->setVisible(false);
    graphChartView = new QChartView(graphChart);
    graphChartView->setRenderHint(QPainter::Antialiasing);
    tabWidget->addTab(graphChartView,"Graph");

    set = new QBarSet("Number");
    histogramSeries = new QStackedBarSeries();
    *set << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;
    histogramSeries->append(set);
    histogramChart = new QChart();
    histogramChart->addSeries(histogramSeries);
    histogramChart->setTitle("Histogram");
    histogramChart->setAnimationOptions(QChart::SeriesAnimations);
    axis = new QBarCategoryAxis();
    histogramChart->createDefaultAxes();
    histogramChart->setAxisX(axis, histogramSeries);
    histogramChart->legend()->setVisible(false);
    histogramChartView = new QChartView(histogramChart);
    histogramChartView->setRenderHint(QPainter::Antialiasing);
    histogramChart->axisY()->setRange(0.0,2);
    tabWidget->addTab(histogramChartView,"Histogram");

    connect(connectButton,&QPushButton::clicked,this,&Interface::signalFromConnectButton);
    connect(connectButton,&QPushButton::clicked,this,&Interface::blockLineEdit);
    connect(resetButton,&QPushButton::clicked,this,&Interface::signalFromResetButton);
}

QString Interface::getIp() {
    return ipLine->text();
}

QString Interface::getPort(){
    return portLine->text();
}

void Interface::blockLineEdit() {
    portLine->setDisabled(true);
    ipLine->setDisabled(true);
}

Interface::~Interface(){
    tabWidget->deleteLater();
    ipLabel->deleteLater();
    ipLabel->deleteLater();
    ipLine->deleteLater();
    label->deleteLater();
    portLabel->deleteLater();
    portLine->deleteLater();
    connectButton->deleteLater();
    horizontalLayout->deleteLater();
    mainLayout->deleteLater();
    lowerLayout->deleteLater();
    resetButton->deleteLater();
    graphSeries->deleteLater();
    graphChart->deleteLater();
    graphChartView->deleteLater();
    set->deleteLater();
    histogramChart->deleteLater();
    axis->deleteLater();
    histogramChartView ->deleteLater();
}

void Interface::plotGraph(QList<double> &data) {
    static int count = 0;
    static double Y = 0;
    if (data.size() > count) {
        graphSeries->append(count,data[count]);
        graphChart->axisX()->setRange(0.0,count);
        graphChart->axisY()->setRange(data[count] < 0 ? data[count]-10:0, data[count] > Y?data[count]+10.0:Y+10.0);
        graphChart->update();
        Y = data[count] > Y? data[count]:Y;
        count++;
    }
}

void Interface::plotHistogram(QList<double> &data){
    static int count = 0;
    static int barMax = 0;
    static int hight = 2;
    if (data.size() > count ){
        static double max = 0;
        if (max < data[count]) {
            max = data[count];
            barMax = (max/10 - (int(max/10))) > 0 ? max/10 + 1 : max/10;
            for (int i = 0; i < 10; i++){
                axis->replace(axis->at(i),QString::number(barMax*i)+"-"+QString::number(barMax*(i+1)));
            }
            histogramSeries->remove(set);
            set = new QBarSet("Number");
            *set << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;
            histogramSeries->append(set);
            hight = 2;
            for (int i = 0; i <= count; i++){
                for (int j = 0; j < 10; j++){
                    if ((data[i] >= barMax*j) && (data[i] <= barMax*(j+1))){
                        set->replace(j,(set->at(j))+1);
                        if (hight < set->at(j)){
                            histogramChart->axisY()->setRange(0.0,set->at(j)+1);
                            hight = set->at(j)+1;
                        }
                        break;
                    }
                }
            }
        } else {
            for (int j = 0; j < 10; j++){
                if ((data[count] >= barMax*j) && (data[count] <= barMax*(j+1))){
                    set->replace(j,(set->at(j))+1);
                    if (hight < set->at(j)){
                        histogramChart->axisY()->setRange(0.0,set->at(j)+1);
                        hight = set->at(j)+1;
                    }
                    break;
                }
            }
        }
        count++;
    }
}

    /*void Interface::plotHistogram(QList<double> &data){
    //usleep(20000);
    int size = data.size();
    static int lastSize = 0;
    //if (size > 0 && ((size - lastSize) > 80)){
    if (size > 0 && (size != lastSize)){
        double max = data[0];
        for (int i = 0; i < size; i++){
            max = (max < data[i] ? data[i] : max);
        }
        int barMax = (max/10 - (int(max/10))) > 0 ? max/10 + 1 : max/10;
        for (int i = 0; i < 10; i++){
            axis->replace(axis->at(i),QString::number(barMax*i)+"-"+QString::number(barMax*(i+1)));
        }
        histogramSeries->remove(set);
        set = new QBarSet("Number");
        *set << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;
        histogramSeries->append(set);
        int hight = 2;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < 10; j++){
                if ((data[i] >= barMax*j) && (data[i] <= barMax*(j+1))){
                    set->replace(j,(set->at(j))+1);
                    if (hight < set->at(j)){
                        histogramChart->axisY()->setRange(0.0,set->at(j)+1);
                        hight = set->at(j)+1;
                    }
                    break;
                }
            }
        }
        lastSize = size;
    }
}*/
