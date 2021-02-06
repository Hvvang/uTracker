#include "connection.h"
#include "server.h"

Connection::Connection(QObject *parent) : QObject(parent) {
    m_parent = parent;
    m_ssl_socket = std::make_shared<QSslSocket>(this);

}

Connection::~Connection() {
//    m_socket->abort();
//    delete m_socket;
    qobject_cast<Server *>(m_parent)->deleteConnection(this);
}

void Connection::doConnect(qintptr socket_id) {
    m_ssl_socket->setSocketDescriptor(socket_id);

//    connect(m_socket, &QTcpSocket::disconnected,this, &Connection::disconnected);
//    connect(m_socket, &QTcpSocket::readyRead, this, &Connection::readyRead);
//    connect(this, &Connection::sendResponse, this, &Connection::writeToSocket);


//    connect(m_ssl_socket.get(), SIGNAL(encrypted()), this, SLOT(encrypted()));
    connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Connection::encrypted);

    connect(m_ssl_socket.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(m_ssl_socket.get(), SIGNAL(disconnected()), this, SLOT(disconnected());
    connect(m_ssl_socket.get(), SIGNAL(connected()),this, SLOT(connected()));
    connect(m_ssl_socket.get(), SIGNAL(sslErrors(QList)), this, SLOT(socketSslErrors(QList));
    connect(m_ssl_socket.get(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));


}

QByteArray Connection::getTask() const {
    return m_task;
}

void Connection::writeToSocket(const QByteArray &data) {
    QByteArray buffer;
    m_socket->write(buffer.setNum(data.size()));
    m_socket->write("\n" + data);
}

void Connection::disconnected() {
    this->deleteLater();
}

void Connection::readyRead() {
    while (!m_socket->atEnd()) {
        QByteArray size = m_socket->readLine();
        m_task = m_socket->read(size.toInt());
        qobject_cast<Server *>(m_parent)->setNewTask(this);
    }
}