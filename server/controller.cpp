#include "controller.h"
#include "unistd.h"

Controller::Controller() {  
    interface = new Interface();
    interface->show();
    connect(interface,&Interface::signalFromConnectButton,this,&Controller::listenUdp);
    connect(interface,&Interface::signalFromResetButton,this,&Controller::resetGraph);
}

Controller::~Controller() {

}
void Controller::startDrawingPlots(){
    while (true){
        //usleep(10000);
        interface->plotGraph(server->getData());
        //interface->plotHistogram(server->getData());
    }
}

void Controller::resetGraph() {
    server->clearList();
}

void Controller::listenUdp() {
    qDebug() << QThread::currentThreadId();
    server = new Server(interface->getIp(), interface->getPort().toInt());
    QThread *threadForServer = new QThread();
    server->moveToThread(threadForServer);
    connect(threadForServer, &QThread::started, server, &Server::initSocket);
    threadForServer->start();
    QThread *threadForController = new QThread();
    this->moveToThread(threadForController);
    connect(threadForController, &QThread::started, this, &Controller::startDrawingPlots);
    threadForController->start();
}
