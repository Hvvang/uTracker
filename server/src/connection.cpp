#include "connection.h"
#include "server.h"

Connection::Connection(QObject *parent) : QObject(parent) {
    m_parent = parent;
}

Connection::~Connection() {
    m_socket->abort();
    delete m_socket;
    qobject_cast<Server *>(m_parent)->deleteConnection(this);
    qDebug() << "connection is deleted...";
}

void Connection::doConnect(qintptr handle) {
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::disconnected,this, &Connection::disconnected);
    connect(m_socket, &QTcpSocket::readyRead,this, &Connection::readyRead);

    m_socket->setSocketDescriptor(handle);
    qDebug() << "connection is made...";
}

QByteArray Connection::getTask() const {
    return m_task;
}

void Connection::write(QByteArray array) {
    m_socket->write(array);
}

void Connection::disconnected() {
    qDebug() << "disconnected...";
    this->deleteLater();
}

void Connection::readyRead() {
    qDebug() << "reading...";
    m_task = m_socket->readAll();
    qobject_cast<Server *>(m_parent)->setNewTask(this);
}