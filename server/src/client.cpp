#include "client.hpp"
#include <QDebug>
#include <QCoreApplication>

TcpSocket::TcpSocket(QObject *parent) : QObject(parent), mTcpSocket(new QTcpSocket(this))
{
    mTcpSocket->connectToHost("10.111.2.1", 6000);
    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}


void TcpSocket::onReadyRead()
{
    QByteArray datas = mTcpSocket->readAll();
    qDebug() << QString(datas.toStdString().c_str());
}