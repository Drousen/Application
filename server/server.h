#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>
#include <QThread>

class Server:public QObject{
    Q_OBJECT
private:
    QUdpSocket *serverSocket;
    QHostAddress ip;
    int port;
    QList<double> data;
public:
    Server(QString ip, int port);
    ~Server();
    void readDatagrams();
    QList<double> &getData();
    void clearList();
public slots:
    void initSocket();
};

#endif // SERVER_H
