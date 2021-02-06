#include <QSslConfiguration>
#include "connection.h"
#include "server.h"
#include "loggingcategories.h"

Connection::Connection(QObject *parent) : QObject(parent) {
    m_parent = parent;
    m_ssl_socket = std::make_shared<QSslSocket>(this);


//    m_ssl_socket->setProtocol(QSsl::SslV3);
    m_ssl_socket->setSocketOption(QAbstractSocket::KeepAliveOption, true);
}

Connection::~Connection() {
//    m_socket->abort();
//    delete m_socket;
//    qobject_cast<Server *>(m_parent)->deleteConnection(this);
}

bool Connection::setSocket(qintptr socket_id) {

    if (m_ssl_socket->setSocketDescriptor(socket_id)) {
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
        config.setProtocol(QSsl::TlsV1_2);
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        m_ssl_socket->setSslConfiguration(config);
        m_ssl_socket->startServerEncryption();
//    m_ssl_socket->setLocalCertificate();
//    m_ssl_socket->setPrivateKey();

        return true;
    } else {
        qDebug(logDebug) << "set Socket false";
        return false;
    }
}

QByteArray Connection::getTask() const {
    return m_task;
}

void Connection::writeToSocket(const QByteArray &data) {
    QByteArray buffer;
    m_ssl_socket->write(data);

//    m_socket->write(buffer.setNum(data.size()));
//    m_socket->write("\n" + data);
}

void Connection::disconnected() {
    this->deleteLater();
}

void Connection::readyRead() {
    /*
    while (!m_socket->atEnd()) {
        QByteArray size = m_socket->readLine();
        m_task = m_socket->read(size.toInt());
        qobject_cast<Server *>(m_parent)->setNewTask(this);
    }
     */
}