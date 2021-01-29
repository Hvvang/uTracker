#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class Client: public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void doConnect();

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
};