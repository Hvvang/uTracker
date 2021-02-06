#include "server.h"
#include "loggingcategories.h"

Server::Server(quint16 _port, QObject *parent) : QTcpServer(parent), m_port(_port) {
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

bool Server::startServer() {
//    Server
//    setSslLocalCertificate("~/Downloads/Qt-SslServer-master/example/Server/Debug/debug/sslserver.pem");
//    Server.setSslPrivateKey("~/Downloads/Qt-SslServer-master/example/Server/Debug/debug/sslserver.key");
//    Server.setSslProtocol(QSsl::TlsV1_2);
//    https://sidstudio.com.ua/sidstudio-blog/sozdanie-servera-na-baze-qt-s-ispolzovaniem-ssl-sertifikatov-chast-1


    if (!this->listen(QHostAddress::Any, m_port)) {
        qWarning(logWarning) << "Server did not start!";
        return false;
    }
    qInfo(logInfo()) << "Server started!";
    return true;
}

void Server::incomingConnection(qintptr handle) {

    qInfo(logInfo()) << "new incomingConnection ";
    Connection *newConnection = new Connection(this);
    newConnection->setSocket(handle);
    m_connections.push_back(newConnection);
}

void Server::deleteConnection(Connection *ptr) {
    m_connections.erase(m_connections.begin() + m_connections.indexOf(ptr));
}

void Server::setNewTask(Connection *ptr) {
    Runnable *task = new Runnable(ptr);

    task->setAutoDelete(true);
    task->setMutex(m_mutex);
    task->setTask(ptr->getTask());
    m_pool->start(task);
}
