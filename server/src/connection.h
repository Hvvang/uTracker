#pragma once

#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QMutex>
#include <QSslSocket>
#include <QSslKey>

class Connection : public QObject {
Q_OBJECT
public:
    explicit Connection(qintptr socket_id, std::shared_ptr<QSslConfiguration> config, QObject* parent = nullptr);
    ~Connection() override;
    std::shared_ptr<QSslSocket> getSocket() const { return m_ssl_socket; }

    QByteArray getTask() const;

public slots:
    void writeToSocket(const QByteArray& data);
    void disconnected();
    void Read();
    void printErrors(QList<QSslError> errors) const;
    void printError(const QSslError& error) const;
    void printData();
    void modeChanged(QSslSocket::SslMode mode);

signals:
    void disconnectSocket(qintptr id);
    void sendResponse(const QByteArray &data);

private:
    std::shared_ptr<QSslSocket> m_ssl_socket;
    qintptr m_socket_id;  // TCP socket descriptor
    QByteArray m_task;
    QObject* m_parent;
    std::shared_ptr<QSslConfiguration> m_config;

    QSslKey key;
    QSslCertificate cert;

    bool setSocket();
};
