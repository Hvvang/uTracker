//
// Created by Artem Shemidko on 21.05.2022.
//

#ifndef UTRACKERSERVER_SERVER_H
#define UTRACKERSERVER_SERVER_H

#include <QSslSocket>
#include <QTcpServer>
#include "SSLSocket.h"

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(const quint16 port, QObject *parent = nullptr);
    ~Server() override;

    void Start(quint16 port = 0);

    static Server &Initialize(const quint16 port, QObject *parent = nullptr);

public slots:

    void Notify(SSLSocket &, const QByteArray &);
    void NotifyAll(const QByteArray &);

protected:

    void incomingConnection(qintptr socketDescriptor) override;


private slots:

    void OnNewConnection();

    void OnSocketClosed();

    void OnHandshake();

    void OnMessageReceived();

private:
    QList<SSLSocket *> Connections;
};


#endif //UTRACKERSERVER_SERVER_H
