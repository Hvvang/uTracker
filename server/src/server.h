#pragma once

#include <QTcpServer>
#include <QThreadPool>
#include <QVector>
#include <QDebug>

#include "connection.h"

#define MAX_THREAD_COUNT 5

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server() override;

    void startServer();

protected:
    void incomingConnection(qintptr handle) override;

signals:

public slots:
    void setNewTask(Connection *ptr);

private:
    QThreadPool *m_pool;
    QVector<Connection *> m_connections;
};
