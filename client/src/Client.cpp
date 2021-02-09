//
// Created by Artem Shemidko on 03.02.2021.
//

#include "Client.h"
#include <QHostAddress>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include "AuthorisationResponseHandler.h"
#include "Router.h"

Client* Client::m_instance = nullptr;

Client::Client(const QHostAddress &host, const quint16 port, QObject *parent)
    : QObject(parent) {

    switchWindow(Ui::Root, Ui::AuthWindow);

    m_socket.connectToHost(QHostAddress::LocalHost, port);

    connect(&m_socket, &QTcpSocket::connected, this, [=]{
        qDebug() << "Client successfully connected to server.";

        initResponseHandlers();

        connect(&m_socket, &QTcpSocket::bytesWritten, this, &Client::bytesWritten);
        connect(&m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
        connect(&m_socket, &QTcpSocket::disconnected, this, []{
            qDebug() << "disconnected...";
        });

    });
    m_instance = this;
}


void Client::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead() {
    qDebug() << "RESPONSE FROM SERVER:\n";
    qDebug() << m_socket.readAll();
    emit responseHandled(m_socket.readAll());
}

void Client::deinitResponseHandlers() {
}

void Client::initResponseHandlers() {
    AuthorisationResponseHandler authHandler;

    connect(this, &Client::responseHandled, &authHandler, &AuthorisationResponseHandler::handled);
}

void Client::switchWindow(const Client::Ui &from, const Client::Ui &to) {
    Q_UNUSED(from);
    QUrl url;

    if (to == Ui::AuthWindow) {
        url = "qrc:/authwindow/Authorisation.qml";
    }
    else if (to == Ui::MainWindow) {
        url = "qrc:/mainwindow/main.qml";
    }
    m_router->loadWindow(url);
}

Client *Client::singleton() {
    if (!m_instance) {
        m_instance = new Client();
    }
    return m_instance;
}

void Client::switchPanel(const Client::Ui &from, const Client::Ui &to) {
    Q_UNUSED(from);
    QUrl url;

    switch(to) {
        case Ui::WorkFlows:
            url = "qrc:/authhwindow/authorisation.qml"; break;
        case Ui::DailyPlane:
            url = "qrc:/authhwindow/authorisation.qml"; break;
        case Ui::Contacts:
            url = "qrc:/authhwindow/authorisation.qml"; break;
        case Ui::Calendar:
            url = "qrc:/authhwindow/authorisation.qml"; break;
        case Ui::Statistic:
            url = "qrc:/authhwindow/authorisation.qml"; break;
        case Ui::Kanban:
            url = "qrc:/authhwindow/authorisation.qml"; break;
    }
    m_router->loadPanel(url);
}

void Client::saveToken(const QString &type, const QString &value) {
    QFile file(AUTH_CONFIGURE_FILE);

    if (!file.open(QIODevice::ReadWrite)) {
        return;
    }

    QJsonObject json = QJsonDocument().fromJson(file.readAll()).object();
    json[type] = value;

    QJsonDocument document;
    document.setObject(json);
    file.write(document.toJson(QJsonDocument::Indented));
}

QString Client::getToken(const QString &type) {
    QFile file(AUTH_CONFIGURE_FILE);

    if (!file.open(QIODevice::ReadWrite)) {
        return QString();
    }

    auto json = QJsonDocument().fromJson(file.readAll()).object();
    return json.value(type).toString();
}

