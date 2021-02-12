//
// Created by Artem Shemidko on 03.02.2021.
//

#ifndef UTRACKER_CLIENT_H
#define UTRACKER_CLIENT_H


#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QQuickItem>

#include "googleauth.h"

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

    enum class RequestType {
        AUTO_OAUTH = 0,
        AUTO_AUTH = 1,
        SIGN_UP = 2,
        SIGN_IN = 3,
    };

    enum class ResponseType {
        AUTO_OAUTH = 0,
        AUTO_AUTH = 1,
        SIGN_UP = 2,
        SIGN_IN = 3,
        LOG_OUT = 4,
        ERROR = 5,
    };

    Client(QQmlApplicationEngine *engine = nullptr, const QHostAddress &host = QHostAddress::LocalHost, const quint16 port = 5000, QObject *parent = nullptr);

    void initResponseHandlers();
    void deinitResponseHandlers();
    void saveToken(const QString &type, const QString &value);
    QString getToken(const QString &type);
    static Client* singleton();

    void autoSignIn();

    Q_INVOKABLE void googleAuthorize();
    Q_INVOKABLE void authorize(const QString &email, const QString &password);
    Q_INVOKABLE void registrate(const QString &email, const QString &password, const QString &name, const QString &surname);


protected:
    static Client* m_instance;

signals:
    void notification(const QString &msg);

    void request(const QString &);
    void responseHandled(const QByteArray &);

    void signUpResponse(const QByteArray &);
    void signInResponse(const QByteArray &);
    void logOutResponse(const QByteArray &);
    void errorResponse(const QByteArray &);

public slots:
    void bytesWritten(qint64 bytes);
    void readyRead();
    void send(const QString &);

private:
    QTcpSocket m_socket;
    QQmlApplicationEngine *m_engine{nullptr};
    GoogleAuth *m_googleInstance{nullptr};
};

#define m_client Client::singleton()

#endif //UTRACKER_CLIENT_H
