#ifndef CLIENT_H
#define CLIENT_H

#include <QFile>
#include <QDir>
#include <iostream>
#include <QUdpSocket>
#include <QRegExp>
#include <unistd.h>
#include <QHostAddress>

class Client{
private:
    QHostAddress ip;
    quint16 port;
    QUdpSocket *clientSocket;
public:
    Client(QString ip, quint16 port);
    ~Client();
    void sendData();
   // static void *startThread(void * c);
};
#endif // CLIENT_H
