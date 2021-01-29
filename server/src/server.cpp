#include "server.h"
#include "thread.h"

Server::Server(QObject *parent) : QTcpServer(parent) {

}

void Server::startServer() {
    int port = 8989;

    if (!this->listen(QHostAddress::Any,port))
        qDebug() << "Could not start server";
    else
        qDebug() << "Listening to port " << port << "...";
}

void Server::incomingConnection(qintptr socketDescriptor) {
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    Thread *thread = new Thread(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be deleted later
    connect(thread, &Thread::finished, thread, &Thread::deleteLater);

    thread->start();
}