//
// Created by Artem Shemidko on 21.05.2022.
//

#include <QNetworkInterface>
#include <Core.h>
#include "CryptoSSL.h"
#include "Server.h"

Server::Server(const quint16 port, QObject *parent)
    : QTcpServer(parent)
    , SSLSocket(this)
{
    Start(port ? port : DefaultPort);
    InitializeSSLSocket();
}


Server::~Server() {
    // Maybe will be needed for closing thread pool
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    if (SSLSocket.setSocketDescriptor(socketDescriptor)) {
        addPendingConnection(&SSLSocket);
        SSLSocket.startServerEncryption();
    } else {
        SSLSocket.close();
    }
}

void Server::ready(){
    qDebug() << "encrypted";
}

void Server::printData(){
    QByteArray array = SSLSocket.read(SSLSocket.bytesAvailable());
    qDebug() << array;
}

void Server::InitializeSSLSocket() {

    SSLSocket.setLocalCertificate(Crypto::SSLCert);
    SSLSocket.setPrivateKey(Crypto::SSLKey);
    SSLSocket.setSocketOption(QAbstractSocket::KeepAliveOption, true );

    connect(&SSLSocket, SIGNAL(encrypted()), this, SLOT(ready()));
    connect(&SSLSocket, SIGNAL(readyRead()), this, SLOT(printData()) );
}

Server &Server::Initialize(const quint16 port, QObject *parent) {
    static Server Instance(port, parent);
    return Instance;
}

void Server::Start(quint16 port) {
    if (!listen(QHostAddress::LocalHost, port)) {
        qWarning() << "Start listen port" << port << "failed";
        close();
        return;
    }
    else {
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


