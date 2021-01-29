#pragma once

#include "thread.h"

#include <QTcpServer>

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};
