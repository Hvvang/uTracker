#include "client.h"

Client::Client(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
}

void Client::doConnect(char *ip, int port) {
    connect(m_socket, &QTcpSocket::connected,this, &Client::connected);
    connect(m_socket, &QTcpSocket::disconnected,this, &Client::disconnected);
    connect(m_socket, &QTcpSocket::bytesWritten,this, &Client::bytesWritten);
    connect(m_socket, &QTcpSocket::readyRead,this, &Client::readyRead);

    qDebug() << "connecting...";

    // this is not blocking call
    m_socket->connectToHost(ip, port);

    // we need to wait...
    if (!m_socket->waitForConnected(5000))
        qDebug() << "Error: " << m_socket->errorString();
}

void Client::connected() {
    qDebug() << "connected...";
    m_socket->write("HELLA");
}

void Client::disconnected() {
    qDebug() << "disconnected...";
}

void Client::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead() {
    qDebug() << "RESPONSE FROM SERVER:\n";

    qDebug() << m_socket->readAll();
}