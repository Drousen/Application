#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "interface.h"
#include "client.h"
#include <QObject>
#include <QThread>

class Controller:public QObject{
    Q_OBJECT
private:
    Interface *interface;
    Client *client;
public:
    Controller();
    Controller(char *ip, char *port);
    ~Controller();
    void start();
};

#endif // CONTROLLER_H
