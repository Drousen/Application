#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "interface.h"
#include "server.h"
#include <QObject>
#include <QThread>
#include <QByteArray>

class Controller:public QObject {
Q_OBJECT
private:
    Interface *interface;
    Server *server;
public:
    Controller();
    ~Controller();
private slots:
    void startDrawingPlots();
    void resetGraph();
    void listenUdp();
};

#endif // CONTROLLER_H
