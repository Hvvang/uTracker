#include <QSslConfiguration>
#include "client.h"
#include "loggingcategories.h"

// в сертификате должен указать  в поле Common Name адрес 127.0.0.1. ...


Client::Client(QObject* parent) :QObject(parent)
{
    m_ssl_socket = std::make_shared<QSslSocket>();
    m_request = std::make_unique<AbstractRequest>(m_ssl_socket);
    configSSL();
}

Client::~Client()
{
    qDebug(logDebug) << "Client destructor";
//    m_ssl_socket->abort();
}

void Client::doConnect(char* host, int port)
{

//    connect(m_ssl_socket.get(), &QTcpSocket::disconnected, this, &Client::disconnected);
//    connect(m_ssl_socket.get(), &QTcpSocket::readyRead, this, &Client::readyRead);
    if (!m_ssl_socket->waitForConnected(5000))
        qDebug() << "Error: " << m_ssl_socket->errorString();

    m_ssl_socket->connectToHostEncrypted(host, port);
//    this->m_ssl_socket->addCaCertificates("key.pem");
    if (this->m_ssl_socket->waitForEncrypted()) {
        qDebug() << " connected to server ";
        this->m_ssl_socket->write("hello tls");
        if (this->m_ssl_socket->waitForBytesWritten()) {
            qDebug() << "send msg";
        }
        else {
            qDebug(logDebug()) << m_ssl_socket->errorString();
        }
    }
    else {
        qDebug(logDebug()) << "error:" << m_ssl_socket->errorString();
    }
}

void Client::disconnected()
{
    this->deleteLater();
}

void Client::readyRead()
{
    while (!m_ssl_socket->atEnd()) {
        QByteArray size = m_ssl_socket->readLine();
        qDebug() << m_ssl_socket->read(size.toInt());
    }
}

void Client::configSSL()
{
    QSslConfiguration config = m_ssl_socket->sslConfiguration();
    const auto certs = QSslCertificate::fromPath("./CA/client.pem", QSsl::Pem);
    config.addCaCertificate(certs.constFirst());
    config.setProtocol(QSsl::TlsV1_3);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_ssl_socket->setSslConfiguration(config);
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
