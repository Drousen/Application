#include "server.h"

Server::Server(QString ip, int port){
    this->ip = QHostAddress(ip);
    this->port = port;
}

Server::~Server() {

}

void Server::initSocket() {
    qDebug() << QThread::currentThreadId();
    serverSocket = new QUdpSocket();
    serverSocket->bind(ip, port);
    connect(serverSocket, &QUdpSocket::readyRead, this, &Server::readDatagrams);
}

void Server::readDatagrams() {
    QNetworkDatagram datagram = serverSocket->receiveDatagram();
    data << datagram.data().toDouble();
}

QList<double> &Server::getData() {
    return data;
}

void Server::clearList() {
    data.clear();
}
