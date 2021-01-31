#pragma once

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include "Responses.h"

class Thread : public QThread {
    Q_OBJECT
public:
    explicit Thread(qintptr ID, QObject *parent = nullptr);

    void run() override;
    void parseJSON(QJsonDocument itemDoc);

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    Responses *m_response;
};