#include "client.h"

Client::Client(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
}

void Client::doConnect() {
    connect(socket, &QTcpSocket::connected,this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected,this, &Client::disconnected);
    connect(socket, &QTcpSocket::bytesWritten,this, &Client::bytesWritten);
    connect(socket, &QTcpSocket::readyRead,this, &Client::readyRead);

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("127.0.0.1", 8989);

    // we need to wait...
    if (!socket->waitForConnected(5000))
        qDebug() << "Error: " << socket->errorString();
}

void Client::connected() {
    qDebug() << "connected...";

    // Hey server, tell me about you.
    socket->write("msg to the server");
}

void Client::disconnected() {
    qDebug() << "disconnected...";
}

void Client::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead() {
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}