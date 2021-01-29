#pragma once

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class Thread : public QThread {
    Q_OBJECT
public:
    explicit Thread(qintptr ID, QObject *parent = nullptr);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};