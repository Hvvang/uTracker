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

    void testConnect() const;
    void testRequestLoop();

signals:

public slots:
//    void disconnected();
//    void readyRead();

public slots:
    void readyRead();
    void disconnected();
    void connectSuccess();
    void sslErrors(const QList<QSslError> &errors);
//    void encrypted();
//    void connected();
//    void socketError(QAbstractSocket::SocketError error);
//    void socketSslErrors(const QList &list);


private:
    std::shared_ptr<QSslSocket> m_ssl_socket;
    std::unique_ptr<AbstractRequest> m_request;
    bool configSSL();

    void reconnect();  // implement reconnection when break
};