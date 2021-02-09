#include <QSslConfiguration>
#include <QFile>
#include <QSslKey>
#include "client.h"
#include "loggingcategories.h"

Client::Client(QObject* parent) :QObject(parent)
{
    m_ssl_socket = std::make_shared<QSslSocket>();
    m_request = std::make_unique<AbstractRequest>(m_ssl_socket);
    connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Client::connectSuccess);
    connect(m_ssl_socket.get(), &QSslSocket::readyRead, this, &Client::readyRead);
    connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Client::disconnected);
    connect(m_ssl_socket.get(), SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
    configSSL();
}

Client::~Client()
{
    qDebug(logDebug) << "Client destructor";
//    m_ssl_socket->abort();
}

void Client::doConnect(char* host, int port)
{
    qDebug(logDebug()) << "doConnect to host " << host;
    m_ssl_socket->connectToHostEncrypted(host, port);  // start a secure connection, starts an immediate SSL handshake
    // once the connection has been established.

    if (m_ssl_socket->waitForEncrypted(50000)) {
        m_ssl_socket->write("new client Suceeded");
        qDebug() << " connected to server ";
        /*
        if (m_ssl_socket->waitForBytesWritten()) {
            qDebug(logDebug()) << "doConnect, socket mode =" << m_ssl_socket->mode();
        }
        else {
            qDebug(logDebug()) << m_ssl_socket->errorString();
        }
         */
    }
    else {
        qDebug(logDebug()) << "error connection to server :" << m_ssl_socket->errorString();
        exit(1);
    }

//    m_ssl_socket->startClientEncryption();
}

void Client::disconnected()
{
    qDebug(logDebug()) << "server::disconnected";
//    reconnect();
//    this->deleteLater();
}

void Client::readyRead()
{
    while (!m_ssl_socket->atEnd()) {
        QByteArray size = m_ssl_socket->readLine();
        qDebug() << m_ssl_socket->read(size.toInt());
    }
}

bool Client::configSSL()
{
    QSslConfiguration config;
    QByteArray key;
    QByteArray cert;

    QFile file_key("./CA/client2.key");
    if (file_key.open(QIODevice::ReadOnly)) {
        key = file_key.readAll();
        file_key.close();
    }
    else {
        qDebug() << "error key " << file_key.errorString();
        return false;
    }

    QFile file_cert("./CA/client2.pem");
    if (file_cert.open(QIODevice::ReadOnly)) {
        cert = file_cert.readAll();
        file_cert.close();
    }
    else {
        qDebug() << "error cert " << file_cert.errorString();
        return false;
    }
    QSslKey ssl_key(key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
    QSslCertificate ssl_cert(cert, QSsl::Pem);
    config.setLocalCertificate(ssl_cert);
    config.setPrivateKey(ssl_key);
//    config.setProtocol(QSsl::TlsV1_2);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_ssl_socket->setSslConfiguration(config);
    return true;
}

void Client::testConnect() const
{
    m_ssl_socket->write("hello");
    qDebug(logDebug()) << "testConnect, socket mode =" << m_ssl_socket->mode();
}

void Client::testRequestLoop()
{
    QString email = "NazarDykyy@gmail.com";
    QString login = "ndykyy";
    QString pass = "21453#gs8kFSdfD1F244iuSn";
    QString name = "Nazar";
    QString surname = "Dykyy";

    m_request->signUp(email, login, pass, name, surname);
    m_request->signIn(email, login, pass);
    m_request->autoSignIn("token");
    m_request->autoSignInWithGoogle("token");
    m_request->logOut();
}

void Client::connectSuccess()
{
    qInfo(logInfo()) << "handshake success, state = " << m_ssl_socket->state();
}


void Client::sslErrors(const QList<QSslError> &errors)
{
            foreach (const QSslError &error, errors)
            qDebug() << error.errorString();
}

//    m_ssl_socket->setLocalCertificate(ssl_cert);
//    m_ssl_socket->setPrivateKey(ssl_key);
//    const auto list_certs = QSslCertificate::fromPath("./CA/client.pem", QSsl::Pem);
//    config.setCaCertificates(list_certs);