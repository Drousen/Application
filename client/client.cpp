#include "client.h"


Client::Client(QString ip, quint16 port) {
    this->ip = QHostAddress(ip);
    this->port = port;
    clientSocket = new QUdpSocket();
}

Client::~Client() {

}

void Client::sendData() {
    QRegExp regExp("*.mat");
    regExp.setPatternSyntax(QRegExp::Wildcard);
    QFileInfoList lastDir;
    while (true){
        sleep(1);
        QDir dir;
        dir.setFilter(QDir::Files);
        dir.setSorting(QDir::Name);
        QFileInfoList CurrentDir = dir.entryInfoList();
        for (int i = 0; i < lastDir.size(); i++){
            CurrentDir.removeOne(lastDir[i]);
        }
        foreach (QFileInfo fileInfo, CurrentDir) {
            if (!regExp.exactMatch(fileInfo.fileName())){
                continue;
            }
            QFile file(fileInfo.fileName());
            if(file.open(QIODevice::ReadOnly)){
                while(!file.atEnd()){
                    QString line = file.readLine();
                    QStringList list = line.split(" ");
                    for (int i = 0; i < list.size();i++){
                        QByteArray Data;
                        Data.append(QByteArray::number(list[i].toDouble()));
                        qDebug() << QByteArray::number(list[i].toDouble());
                        clientSocket->writeDatagram(Data,ip,port);
                        //usleep(40000);
                    }
                }
            }
        }
        lastDir = dir.entryInfoList();
    }
}

/*void *Client::startThread(void *c) {
    ((Client *) c)->sendData();
    return NULL;
}*/

