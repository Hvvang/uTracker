#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QSslSocket>
#include "requests.h"


class Client: public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void doConnect(char *host, int port);
    void testRequestLoop();

signals:

//public slots:
//    void disconnected();
//    void readyRead();

public slots:
    void readyRead();
    void disconnected();
//    void encrypted();
//    void connected();
//    void socketError(QAbstractSocket::SocketError error);
//    void socketSslErrors(const QList &list);


private:
    std::shared_ptr<QSslSocket> m_ssl_socket;
    std::unique_ptr<AbstractRequest> m_request;
    void configSSL();
};