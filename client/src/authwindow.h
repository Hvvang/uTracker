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
    explicit AuthWindow(QObject *parent = nullptr, QQmlEngine *engine = nullptr);

    enum Type {
        AuthToken,
        AccessesToken,
        RefreshToken
    };
    enum RequestType {
        AUTO_OAUTH,
        AUTO_AUTH,
        SIGN_UP,
        SIGN_IN,
    };

    Q_INVOKABLE void signIn(const QString &, const QString &);
    Q_INVOKABLE void signUp(const QString &, const QString &, const QString &, const QString &);
    QString getToken(const Type &);
    void saveTokens(const QString &, const QString &, const QString &);

private:
    void autoSignIn();

public slots:
    void response(const QString &);

signals:
    void request(const QString &);

private:
    QQmlEngine *m_engine;
    GoogleAuth m_googleAuth;
    QQuickView *m_view;
};

#endif // AUTHWINDOW_H
