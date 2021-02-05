#include "client.h"

Client::Client(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
    m_request = new AbstractRequest(m_socket);
}

Client::~Client() {
    m_socket->abort();
    delete m_socket;
    delete m_request;
}

void Client::doConnect(char *ip, int port) {
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    m_socket->connectToHost(ip, port);
    if (!m_socket->waitForConnected(5000))
        qDebug() << "Error: " << m_socket->errorString();
}

void Client::testRequestLoop() {
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

void Client::disconnected() {
    // do something when disconnection happens
}

void Client::readyRead() {
    while (!m_socket->atEnd()) {
        QByteArray size = m_socket->readLine();
        qDebug() << m_socket->read(size.toInt());
    }
}