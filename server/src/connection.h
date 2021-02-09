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
    explicit Connection(qintptr socket_id, std::shared_ptr<QSslConfiguration> config, QObject *parent = nullptr);
    ~Connection() override;
    std::shared_ptr<QSslSocket> getSocket() const { return m_ssl_socket;}

    QByteArray getTask() const;

public slots:

signals:
    void sendResponse(const QByteArray &data);
    void newCon(QTcpSocket *socket);


public slots:
    void writeToSocket(const QByteArray &data);
    void disconnected();
    void readyRead();
    void printErrors(QList<QSslError> errors) const;
    void printError(const QSslError &error) const;
    void printData();
    void modeChanged(QSslSocket::SslMode mode);



private:
    std::shared_ptr<QSslSocket> m_ssl_socket;
    qintptr m_socket_id;  // TCP socket descriptor

    QByteArray m_task;
//    QTcpSocket *m_socket;
    QObject *m_parent;
    std::shared_ptr<QSslConfiguration> m_config;
    bool setSocket();
    bool setSocket2();
};
