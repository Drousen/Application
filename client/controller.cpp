#include "controller.h"

Controller::Controller(){
    interface = new Interface();
    interface->show();
    client = new Client("127.0.0.1",1234); 
    QThread *thread = new QThread;
    moveToThread(thread);
    connect(thread, &QThread::started, this, &Controller::start);
    thread->start();
    //pthread_t sendThread;
    //pthread_create(&sendThread,NULL,Client::startThread, this->client);
}
Controller::~Controller(){

}

void Controller::start(){
    client->sendData();
}
