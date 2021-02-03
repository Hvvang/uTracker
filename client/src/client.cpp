#include "client.h"

Client::Client(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
//    m_request = new Request(m_socket);
}

Client::~Client() {
    m_socket->abort();
    delete m_socket;
//    delete m_request;
}

void Client::doConnect(char *ip, int port) {
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    m_socket->connectToHost(ip, port);
    if (!m_socket->waitForConnected(5000))
        qDebug() << "Error: " << m_socket->errorString();
}

void Client::testRequestLoop() {
//    QByteArray buffer;
//    QDataStream stream(&buffer, QIODevice::WriteOnly);

//    stream << "ND" << "12345678" << "lala@gmail.com" << "Nazar" << "Dykyy";
//    signUp *req = new signUp(m_socket, buffer);
//    signIn *requ = new signIn(m_socket, buffer);
//    autoSignInWithGoogle *reque = new autoSignInWithGoogle(m_socket, buffer);
//    autoSignIn *request = new autoSignIn(m_socket, buffer);

//    request->send();
//    request->send();
//    reque->send();
//    requ->send();
//    req->send();

    QString test("this\nis\none\nrequest\n");
    QByteArray buffer;
    m_socket->write(buffer.setNum(test.size()));
    m_socket->write("\n" + test.toLocal8Bit());
}

void Client::disconnected() {
    this->deleteLater();
}

void Client::readyRead() {
    while (!m_socket->atEnd()) {
        QByteArray size = m_socket->readLine();
        qDebug() << m_socket->read(size.toInt());
    }
}