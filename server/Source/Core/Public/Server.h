//
// Created by Artem Shemidko on 21.05.2022.
//

#ifndef UTRACKERSERVER_SERVER_H
#define UTRACKERSERVER_SERVER_H

#include <QSslSocket>
#include <QTcpServer>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(quint16 port, QObject *parent = nullptr);
    Server(QObject *parent = nullptr);
    ~Server() override;

    void Start(quint16 port = 0);

    static Server &Initialize(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    void InitializeSSLSocket();

private slots:
    void ready();
    void printData();

private:
    QSslSocket SSLSocket;
};


#endif //UTRACKERSERVER_SERVER_H
