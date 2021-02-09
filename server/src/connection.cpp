#include <QSslConfiguration>
#include <QFile>
#include "connection.h"
#include "server.h"
#include "loggingcategories.h"

Connection::Connection(qintptr socket_id, std::shared_ptr<QSslConfiguration> config, QObject* parent) :QObject(
        parent), m_socket_id(socket_id), m_config(config)
{
    qDebug(logDebug()) << "Connection ";
    m_ssl_socket = std::make_shared<QSslSocket>(this);
    m_ssl_socket->setSocketOption(QAbstractSocket::KeepAliveOption, true);
    setSocket();
}

Connection::~Connection()
{
//    qobject_cast<Server *>(m_parent)->deleteConnection(this);
}

bool Connection::setSocket()
{
    if (m_ssl_socket->setSocketDescriptor(m_socket_id)) {
        qDebug(logDebug) << "setSocketDescriptor true, ssl mode " << m_ssl_socket->mode();
        m_ssl_socket->setSslConfiguration(*m_config);

        connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Connection::Read);
//        connect(m_ssl_socket.get(), &QSslSocket::modeChanged, this, &Connection::modeChanged);
//        connect(m_ssl_socket.get(), &QSslSocket::peerVerifyError, this, &Connection::printError);
        connect(m_ssl_socket.get(), QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors),
                [=](const QList<QSslError>& errors) {
                  for (auto err : errors) {
                      qDebug(logDebug()) << err.errorString();
                  }
                });

        connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Connection::disconnected);
//        connect(m_ssl_socket.get(), &QSslSocket::sslErrors, this, &QSslSocket::sslHandshakeErrors);
        connect(this, &Connection::sendResponse, this, &Connection::writeToSocket);

        m_ssl_socket->startServerEncryption();  // initiates the SSL handshake
        printErrors(m_ssl_socket->sslHandshakeErrors());
        qDebug(logDebug()) << "setSocket end,  socket mode =" << m_ssl_socket->mode();
        return true;
    }
    else {
        qDebug(logDebug) << "set Socket false";
//        m_ssl_socket->close();
        return false;
    }

}

void Connection::printData()
{

    QByteArray array = m_ssl_socket->read(m_ssl_socket->bytesAvailable());
    qDebug() << array;
}

QByteArray Connection::getTask() const
{
    return m_task;
}

void Connection::writeToSocket(const QByteArray& data)
{
    QByteArray buffer;
    m_ssl_socket->write(data);

//    m_socket->write(buffer.setNum(data.size()));
//    m_socket->write("\n" + data);
}

void Connection::disconnected()
{
    qDebug("Client Disconnected from Connection");
    emit disconnectSocket(m_socket_id);
//    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
//    clientSocket->deleteLater();
}

void Connection::Read()
{
    qInfo(logInfo()) << "Read  from client";

    while (m_ssl_socket->waitForReadyRead())
        qDebug() << m_ssl_socket->readAll().data();
    /*
    while (!m_ssl_socket->atEnd()) {
        QByteArray size = m_ssl_socket->readLine();

        QByteArray read_task = m_ssl_socket->read(size.toInt());
        qDebug(logDebug()) << read_task.toStdString();
//        m_task = m_ssl_socket->read(size.toInt());
//        qobject_cast<Server*>(m_parent)->setNewTask(this);
    }
*/
}
void Connection::printErrors(QList<QSslError> errors) const
{
    qDebug(logDebug()) << "printErrors" << m_ssl_socket->errorString();

    for (auto error : errors) {
        qDebug(logDebug()) << error.errorString() << "\n";
    }
}
void Connection::printError(const QSslError& error) const
{
    qDebug(logDebug()) << "error peer " << error;
}
void Connection::modeChanged(QSslSocket::SslMode mode)
{
    qDebug(logDebug()) << "ssl mode  " << mode;
    m_ssl_socket->startServerEncryption();  // initiates the SSL handshake
    printErrors(m_ssl_socket->sslHandshakeErrors());
}

//void Connection::displayCertificateInfo()
//{
//    CertificateInfo info;
//    info.setCertificateChain(socket->peerCertificateChain());
//    info.exec();
//}

