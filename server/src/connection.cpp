#include <QSslConfiguration>
#include <QFile>
#include <QSslKey>
#include "connection.h"
#include "server.h"
#include "loggingcategories.h"

Connection::Connection(qintptr socket_id, std::shared_ptr<QSslConfiguration> config, QObject* parent) :QObject(
        parent), m_socket_id(socket_id), m_config(config)
{
    qDebug(logDebug()) << "Connection ";
    m_ssl_socket = std::make_shared<QSslSocket>(this);
    m_ssl_socket->setSocketOption(QAbstractSocket::KeepAliveOption, true);

    setSocket2();
}

Connection::~Connection()
{
//    m_socket->abort();
//    delete m_socket;
//    qobject_cast<Server *>(m_parent)->deleteConnection(this);
}

bool Connection::setSocket2()
{

    if (m_ssl_socket->setSocketDescriptor(m_socket_id)) {
        qDebug(logDebug) << "setSocketDescriptor true";
        qDebug(logDebug()) << "ssl mode 64 " << m_ssl_socket->mode();

        m_ssl_socket->setSslConfiguration(*m_config);

        connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Connection::readyRead);

        connect(m_ssl_socket.get(), &QSslSocket::modeChanged, this, &Connection::modeChanged);

        connect(m_ssl_socket.get(), &QSslSocket::peerVerifyError, this, &Connection::printError);
        connect(m_ssl_socket.get(), QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors),
                [=](const QList<QSslError>& errors) {
                  for (auto err : errors) {
                      qDebug(logDebug()) << err.errorString();
                  }
                });

        connect(m_ssl_socket.get(), &QSslSocket::readyRead, this, &Connection::readyRead);
        connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Connection::disconnected);
        connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Connection::disconnected);
//        connect(m_ssl_socket.get(), &QSslSocket::sslErrors, this, &QSslSocket::sslHandshakeErrors);

//        emit newCon(m_ssl_socket.get());

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
    qDebug("Client Disconnected");
//    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
//    clientSocket->deleteLater();
}

void Connection::readyRead()
{
    qInfo(logInfo()) << "readyRead ";

    while (!m_ssl_socket->atEnd()) {
        QByteArray size = m_ssl_socket->readLine();
        m_task = m_ssl_socket->read(size.toInt());
        qobject_cast<Server*>(m_parent)->setNewTask(this);
    }
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


bool Connection::setSocket()
{

    if (m_ssl_socket->setSocketDescriptor(m_socket_id)) {
        qDebug(logDebug) << "set Socket true";
//    connect(this, &Connection::sendResponse, this, &Connection::writeToSocket);

//    connect(m_ssl_socket.get(), SIGNAL(encrypted()), this, SLOT(encrypted()));

//    connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Connection::encrypted);
        connect(m_ssl_socket.get(), &QSslSocket::readyRead, this, &Connection::readyRead);
        connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Connection::disconnected);
//    connect(m_ssl_socket.get(), &QSslSocket::connected, this, &Connection::connected);
//    connect(m_ssl_socket.get(), &QSslSocket::sslErrors, this, &Connection::sslErrors);


        QSslConfiguration config = m_ssl_socket->sslConfiguration();
//        const auto certs_pem = QSslCertificate::fromPath("./CA/server.pem", QSsl::Pem);
        const auto certs_pem = QSslCertificate::fromPath("./CA/server.root", QSsl::Pem);
//    const auto certs_key = QSslCertificate::fromPath("./CA/server.key", QSsl::Pem);

        config.addCaCertificate(certs_pem.constFirst());
//        config.setProtocol(QSsl::TlsV1_2);
        config.setPeerVerifyMode(QSslSocket::VerifyPeer);
        m_ssl_socket->setSslConfiguration(config);
        m_ssl_socket->startServerEncryption();


//        addPendingConnection(&serverSocket);
//        serverSocket.startServerEncryption();
//    m_ssl_socket->setLocalCertificate();
//    m_ssl_socket->setPrivateKey();

        return true;
    }
    else {
        qDebug(logDebug) << "set Socket false";
        m_ssl_socket->close();
        return false;
    }
}
