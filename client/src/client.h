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

    void doConnect(char *ip, int port);

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *m_socket;
//    Request *m_request;
};