#pragma once

#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QMutex>
#include <QSslSocket>

class Connection : public QObject {
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    ~Connection() override;

    bool setSocket(qintptr socket_id);
    QByteArray getTask() const;

signals:
    void sendResponse(const QByteArray &data);

public slots:
    void writeToSocket(const QByteArray &data);
    void disconnected();
    void readyRead();

private:
    std::shared_ptr<QSslSocket> m_ssl_socket;

    QByteArray m_task;
//    QTcpSocket *m_socket;
    QObject *m_parent;
};
