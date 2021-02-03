#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

#include "requests.h"


class Client: public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void doConnect(char *ip, int port);
    void testRequestLoop();

signals:

public slots:
    void disconnected();
    void readyRead();

private:
    QTcpSocket *m_socket;
    AbstractRequest *m_request;
};