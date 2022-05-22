//
// Created by Artem Shemidko on 21.05.2022.
//

#include <QNetworkInterface>
#include <Core.h>
#include <QSslConfiguration>
#include "CryptoSSL.h"
#include "Server.h"

Server::Server(const quint16 port, QObject *parent)
    : QTcpServer(parent)
{
    Start(port ? port : DefaultPort);
}


Server::~Server() {
    // Maybe will be needed for closing thread pool
    close();
}

Server &Server::Initialize(const quint16 port, QObject *parent) {
    static Server Instance(port, parent);
    return Instance;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    SSLSocket *ServerSocket = new SSLSocket;
    if (ServerSocket->setSocketDescriptor(socketDescriptor)) {
        addPendingConnection(ServerSocket);
    }
    else {
        delete ServerSocket;
    }
}

void Server::OnNewConnection() {
    SSLSocket *Socket = dynamic_cast<SSLSocket *>(nextPendingConnection());
    assert(Socket);

    // QSslSocket emits the encrypted() signal after the encrypted connection is established
    connect(Socket, &SSLSocket::FatalError, this, &Server::OnSocketClosed);
    connect(Socket, &QSslSocket::encrypted, this, &Server::OnHandshake);
    connect(Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnSocketClosed()));

    Socket->Initialize();

    qDebug() << "OnNewConnection";
}

void Server::OnHandshake() {
    SSLSocket *Socket = dynamic_cast<SSLSocket *>(sender());

    assert(Socket);

    connect(Socket, SIGNAL(disconnected()), this, SLOT(OnSocketClosed()));
    connect(Socket, SIGNAL(readyRead()), this, SLOT(OnMessageReceived()));

    Connections.push_back(Socket);

    qDebug() << "OnHandshake";

}

void Server::OnMessageReceived() {
    QSslSocket *Socket = dynamic_cast<QSslSocket *>(sender());
    assert(Socket);

    if (Socket->canReadLine()) {
        QByteArray message;
        while (!Socket->atEnd()) {
            QByteArray size = Socket->readLine();
            message = Socket->read(size.toInt());
        }

        QString sender = QString("%1:%2")
                .arg(Socket->peerAddress().toString())
                .arg(Socket->peerPort());


        QString Message = QString ("[%1] %2 sent: %3")
                    .arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz ap"))
                    .arg(sender)
                    .arg(message.constData());

        qDebug() << Message;
    }
}

void Server::Start(quint16 port) {
    if (!listen(QHostAddress::LocalHost, port)) {
        qWarning() << "Start listen port" << port << "failed";
        close();
        return;
    }
    else {
        connect(this, &Server::newConnection, this, &Server::OnNewConnection);
        foreach (const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces()) {
            QNetworkInterface::InterfaceFlags flags = netInterface.flags();
            if( (bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)){
                foreach (const QNetworkAddressEntry &address, netInterface.addressEntries()) {
                    if(address.ip().protocol() == QAbstractSocket::IPv4Protocol){
                        qDebug() << "Start listening " << address.ip().toString() <<  " on port" << port;
                    }
                }
            }
        }
    }
}

void Server::OnSocketClosed()
{
    SSLSocket *Socket = dynamic_cast<SSLSocket *>(sender());

    assert(Socket);

    Connections.removeOne(Socket);
    Socket->disconnect();
    Socket->deleteLater();
}

void Server::Notify(SSLSocket &InSocket, const QByteArray &InData)
{
    QByteArray buffer;
    InSocket.write(buffer.setNum(InData.size()) + "\n");
    InSocket.write(InData);
}

void Server::NotifyAll(const QByteArray &InData)
{
    foreach (SSLSocket *Socket, Connections) {
        Notify(*Socket, InData);
    }
}



