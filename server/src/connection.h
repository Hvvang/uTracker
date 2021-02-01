#pragma once

#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Connection : public QObject {
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    ~Connection() override;

    void doConnect(qintptr handle);
    QString getTask() const;

signals:

public slots:
    void disconnected();
    void readyRead();

private:
    QString m_task;
    QTcpSocket *m_socket;
    QObject *m_parent;
};
