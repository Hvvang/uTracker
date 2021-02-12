#include "authwindow.h"
#include <QFile>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>
#include <QQuickItem>

#include "Client.h"

AuthWindow::AuthWindow(QObject *parent, QQmlApplicationEngine *engine)
    : QObject(parent) {
    connect(&m_googleAuth, &GoogleAuth::gotToken, m_client, &Client::saveToken);

    engine->rootContext()->setContextProperty("GoogleAuth", &m_googleAuth);
    engine->rootContext()->setContextProperty("Auth", this);

    autoSignIn();
}

void AuthWindow::autoSignIn() {
    QString token;
    QJsonObject json;

    if (token = m_client->getToken("auth_token"); !token.isEmpty()) {
        json["type"] = AUTO_AUTH;
        json["token"] = token;
    } else if (token = m_client->getToken("accesses_token"); !token.isEmpty()) {
        json["type"] = AUTO_OAUTH;
        json["token"] = token;
    } else {
        return;
    }
    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void AuthWindow::signIn(const QString &email, const QString &password) {
    QJsonObject json;

    json["type"] = SIGN_IN;
    json["email"] = email;
    json["password"] = password;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void AuthWindow::signUp(const QString &email, const QString &password, const QString &name, const QString &surname) {
    QJsonObject json;

    json["type"] = SIGN_UP;
    json["email"] = email;
    json["password"] = password;
    json["name"] = name;
    json["surname"] = surname;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}


