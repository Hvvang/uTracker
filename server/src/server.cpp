#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent) {
    m_mutex = new QMutex();
    m_pool = new QThreadPool(this);
    m_pool->setMaxThreadCount(MAX_THREAD_COUNT);
}

Server::~Server() {
    m_mutex->unlock();
    delete m_pool;
    delete m_mutex;
    m_connections.clear();
}

void Server::startServer() {
    if (!this->listen(QHostAddress::Any, 8989)) {
        qDebug() << "Server did not start!";
        exit(EXIT_FAILURE);
    }
}

void Server::incomingConnection(qintptr handle) {
    Connection *newConnection = new Connection(this);
    newConnection->doConnect(handle);

    m_connections.push_back(newConnection);

    qDebug() << m_connections.size();
}

void Server::deleteConnection(Connection *ptr) {
    m_connections.erase(m_connections.begin() + m_connections.indexOf(ptr));
}

void Server::setNewTask(Connection *ptr) {
    Runnable *task = new Runnable(ptr);

    task->setAutoDelete(true);
    task->setMutex(m_mutex);
    m_pool->start(task);
}
