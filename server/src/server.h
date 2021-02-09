#pragma once

#include <QTcpServer>
#include <QThreadPool>
#include <QVector>
#include <QSslKey>

#include "runnable.h"

#define MAX_THREAD_COUNT 5

class Server : public QTcpServer {
Q_OBJECT
public:
    explicit Server(quint16 _port, QObject* parent = nullptr);
    ~Server() override;

    bool startServer();
protected:
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    void deleteConnection(qintptr id);
    void setNewTask(Connection* ptr);

private:
    quint16 m_port;
    QMutex* m_mutex;
    QThreadPool* m_pool;
    QVector<Connection*> m_connections;
    QMap<quint16, Connection*> m_map_connections;
    std::shared_ptr<QSslConfiguration> m_config;

    bool setSsslConfig();
};
