//
// Created by Artem Shemidko on 03.02.2021.
//

#ifndef UTRACKER_CLIENT_H
#define UTRACKER_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>

#define AUTH_CONFIGURE_FILE QCoreApplication::applicationDirPath() + "/.auth_config"

class Client: public QObject {
Q_OBJECT
public:
    enum class Ui {
        Root,
        AuthWindow,
        MainWindow,
        WorkFlows,
        DailyPlane,
        Contacts,
        Calendar,
        Statistic,
        Kanban,
    };

    Client(const QHostAddress &host = QHostAddress::LocalHost, const quint16 port = 5000, QObject *parent = nullptr);

    void initResponseHandlers();
    void deinitResponseHandlers();
    void switchWindow(const Ui &from, const Ui &to);
    void switchPanel(const Ui &from, const Ui &to);
    void saveToken(const QString &type, const QString &value);
    QString getToken(const QString &type);
    static Client* singleton();

protected:
    static Client* m_instance;

signals:
    void responseHandled(const QByteArray &);

public slots:
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket m_socket;
};

#define m_client Client::singleton()

#endif //UTRACKER_CLIENT_H
