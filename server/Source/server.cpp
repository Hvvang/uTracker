#include "server.h"

Server* Server::m_instance = nullptr;

Server::Server(QObject *parent) : QTcpServer(parent) {
    m_mutex = new QMutex();
    m_pool = new QThreadPool(this);
    m_pool->setMaxThreadCount(MAX_THREAD_COUNT);
    m_instance = this;
}

Server::~Server() {
    m_mutex->unlock();
    delete m_pool;
    delete m_mutex;
    m_connections.clear();
}

void Server::startServer(quint16 port) {
    if (!this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server did not start!";
        exit(EXIT_FAILURE);
    }
}

void Server::incomingConnection(qintptr handle) {
    Connection *newConnection = new Connection(this);
    newConnection->doConnect(handle);

    m_connections.push_back(newConnection);
}

void Server::deleteConnection(Connection *ptr) {
    m_connections.erase(m_connections.begin() + m_connections.indexOf(ptr));
}

void Server::sendTo(const int &userId, const QByteArray &data) {
    foreach(const auto &connect, m_connections) {
        if (connect->getUserId() == userId) {
            connect->writeToSocket(data);
            return;
        }
    }
}
void Server::sendToAll(const QByteArray &data) {
    foreach(const auto &connect, m_connections) {
        connect->writeToSocket(data);
    }
}

void Server::setNewTask(Connection *ptr) {
    Runnable *task = new Runnable(ptr);

    task->setAutoDelete(true);
    task->setMutex(m_mutex);
    task->setTask(ptr->getTask());
    m_pool->start(task);
}

Server *Server::singleton() {
    if (!m_instance) {
        m_instance = new Server();
    }
    return m_instance;
}
