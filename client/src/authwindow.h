#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QObject>
#include <QQuickView>
#include <QQmlApplicationEngine>

#include "googleauth.h"

#define AUTH_CONFIGURE_FILE QCoreApplication::applicationDirPath() + "/.auth_config"

class AuthWindow : public QObject
{
    Q_OBJECT
public:
    explicit AuthWindow(QObject *parent = nullptr, QQmlApplicationEngine *engine = nullptr);

    enum RequestType {
        AUTO_OAUTH,
        AUTO_AUTH,
        SIGN_UP,
        SIGN_IN,
    };


private:
    void autoSignIn();

private:
//    QQmlEngine *m_engine;
    GoogleAuth m_googleAuth;
};

#endif // AUTHWINDOW_H
