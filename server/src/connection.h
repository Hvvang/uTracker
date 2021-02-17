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
    explicit Connection(qintptr socket_id, std::shared_ptr<QSslSocket> ssl_socket, QObject* parent = nullptr);
    ~Connection() override;

//    std::shared_ptr<QSslSocket> getSocket() const { return m_ssl_socket; }

    QByteArray getTask() const { return m_task; }
//    void parseJSON(QJsonDocument itemDoc);

public slots:
    void write_to_socket(const QByteArray& data);
    void disconnected();
    void read_from_socket();
    void print_errors(QList<QSslError> errors) const;
    void print_error(const QSslError& error) const;
    void mode_changed(QSslSocket::SslMode mode);

signals:
    void disconnectSocket(qintptr id);
    void sendResponse(const QByteArray& data);
    void new_task(Connection* ptr);

private:
    qintptr m_socket_id;  // TCP socket descriptor
    std::shared_ptr<QSslSocket> m_ssl_socket;
    QByteArray m_task;
    QObject* m_parent;
//    QSslKey key;
//    QSslCertificate cert;
};
