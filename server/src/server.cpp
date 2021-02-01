#include "server.h"
#include "runnable.h"

Server::Server(QObject *parent) : QTcpServer(parent) {
    m_pool = new QThreadPool(this);
    m_pool->setMaxThreadCount(MAX_THREAD_COUNT);
}

Server::~Server() {
    delete m_pool;
    m_connections.clear();
}

void Server::startServer() {
    if (this->listen(QHostAddress::Any, 8989))
        qDebug() << "Server started";
    else
        qDebug() << "Server did not start!";
}

void Server::incomingConnection(qintptr handle) {
    Connection *newConnection = new Connection(this);
    newConnection->doConnect(handle);

    m_connections.push_back(newConnection);
    m_connections.size();
}

void Server::setNewTask(Connection *ptr) {
    Runnable *task = new Runnable(ptr);

    task->setAutoDelete(true);
    m_pool->start(task);
    qDebug() << "pool started";
}
