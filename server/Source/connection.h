#pragma once

#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QMutex>

class Connection : public QObject {
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    ~Connection() override;

    void doConnect(qintptr handle);
    QByteArray getTask() const;

    int getUserId() const;
    void setUserId(const int &id);

signals:
    void sendResponse(const QByteArray &data);

public slots:
    void writeToSocket(const QByteArray &data);
    void disconnected();
    void readyRead();

private:
    QByteArray m_task;
    QTcpSocket *m_socket;
    QObject *m_parent;
    int m_userId = -1;
};
