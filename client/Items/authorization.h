#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>

class Authorization : public QObject
{
    Q_OBJECT
public:
    explicit Authorization(QObject *parent = nullptr);
    ~Authorization() = default;

    Q_INVOKABLE bool signUpHandler(QString login, QString mail, QString password){};
    Q_INVOKABLE bool signInHandler(QString ident, QString password);

private:
    void doServerRequest();
private:
    // Request m_request;
    QString m_mail;
    QString m_login;
    QString m_password;
};

#endif // AUTHORIZATION_H
