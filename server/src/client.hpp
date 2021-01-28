#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpSocket : public QObject
{
Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);

public slots:
    void onReadyRead();

private:
    QTcpSocket *mTcpSocket;
};