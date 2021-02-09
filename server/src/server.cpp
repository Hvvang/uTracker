#include <QFile>
#include <QSslConfiguration>
#include "server.h"
#include "loggingcategories.h"

Server::Server(quint16 _port, QObject* parent) :QTcpServer(parent), m_port(_port)
{
    m_mutex = new QMutex();
    m_pool = new QThreadPool(this);
    m_pool->setMaxThreadCount(MAX_THREAD_COUNT);
    setSsslConfig();
}

Server::~Server()
{
    delete m_pool;
    delete m_mutex;
}

bool Server::startServer()
{
    if (!listen(QHostAddress::LocalHost, m_port)) {
//    if (!listen(QHostAddress("127.0.0.1"), m_port)) {
        qWarning(logWarning) << "Server did not start!";
        return false;
    }
    qInfo(logInfo()) << "Server started!";
    return true;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qInfo(logInfo()) << "new incomingConnection socketDescriptor = " << socketDescriptor;
    Connection* newConnection = new Connection(socketDescriptor, m_config, this);
    m_map_connections[socketDescriptor] = newConnection;
    connect(newConnection, &Connection::disconnectSocket, this, &Server::deleteConnection);
//    addPendingConnection(newConnection->getSocket().get());
}

void Server::deleteConnection(qintptr id)
{
    m_connections.remove(id);
    qDebug(logDebug()) << "remove id " << id;
}

void Server::setNewTask(Connection* ptr)
{
    Runnable* task = new Runnable(ptr);

    task->setAutoDelete(true);
    task->setMutex(m_mutex);
    task->setTask(ptr->getTask());
    m_pool->start(task);
}
bool Server::setSsslConfig()
{
    qDebug(logDebug()) << " setConfig";
    QByteArray key;
    QByteArray cert;
    QByteArray root;
    QSslConfiguration config;

    QFile file_key("./CA/server.key");
    if (file_key.open(QIODevice::ReadOnly)) {
        key = file_key.readAll();
        file_key.close();
    }
    else {
        qDebug() << "error key " << file_key.errorString();
        return false;
    }

    QFile file_cert("./CA/server.pem");
    if (file_cert.open(QIODevice::ReadOnly)) {
        cert = file_cert.readAll();
        file_cert.close();
    }
    else {
        qDebug() << "error cert " << file_cert.errorString();
        return false;
    }
    QFile file_root_cert("./CA/root.pem");
    if (file_root_cert.open(QIODevice::ReadOnly)) {
        root = file_root_cert.readAll();
        file_root_cert.close();
    }
    else {
        qDebug() << "root cert " << file_cert.errorString();
        return false;
    }
    QSslKey ssl_key(key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
    QSslCertificate ssl_cert(cert, QSsl::Pem);
    QSslCertificate root_cert(root, QSsl::Pem);

    config.setLocalCertificate(ssl_cert);
    config.setPrivateKey(ssl_key);
    config.addCaCertificate(root_cert);
//        config.setProtocol(QSsl::TlsV1_2);
    config.setPeerVerifyMode(QSslSocket::VerifyPeer);
    m_config = std::make_shared<QSslConfiguration>(config);
    return true;
}

//
//void Server::write()
//{
//    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
//    qDebug() << clientSocket->readAll();
//    clientSocket->write("Server says Hello");
//}
//

//void Server::disconnected()
//{
//    qDebug("Client Disconnected");
//    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
//    clientSocket->deleteLater();
//}
