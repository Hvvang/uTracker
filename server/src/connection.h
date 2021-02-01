#pragma once

#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QByteArray>

class Connection : public QObject {
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    ~Connection() override;

    void doConnect(qintptr handle);
    void write(QByteArray array);
    QByteArray getTask() const;

signals:

public slots:
    void disconnected();
    void readyRead();

private:
    QByteArray m_task;
    QTcpSocket *m_socket;
    QObject *m_parent;
};
