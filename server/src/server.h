#pragma once

#include <QTcpServer>
#include <QThreadPool>
#include <QVector>
#include <QMap>

#include "runnable.h"

#define MAX_THREAD_COUNT 10

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server() override;

    void startServer(quint16 port = 0);

    void sendTo(const int &userId, const QByteArray &data);

    static Server* singleton();

protected:
    static Server* m_instance;
    void incomingConnection(qintptr handle) override;

signals:

public slots:
    void deleteConnection(Connection *ptr);
    void setNewTask(Connection *ptr);

private:
    QMutex *m_mutex;
    QThreadPool *m_pool;
    QVector<Connection *> m_connections;
};

#define m_server Server::singleton()

