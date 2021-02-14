#include "authwindow.h"
#include <QFile>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>
#include <QQuickItem>


AuthWindow::AuthWindow(QObject *parent, QQmlEngine *engine)
    : QObject(parent)
    , m_engine(engine)
    , m_view(new QQuickView(m_engine, nullptr)) {
    connect(&m_googleAuth, &GoogleAuth::gotToken, this, &AuthWindow::saveTokens);

    engine->rootContext()->setContextProperty("GoogleAuth", &m_googleAuth);
    engine->rootContext()->setContextProperty("Auth", this);

    m_view->setSource(QUrl("qrc:/auth/Authorization.qml"));
    m_view->setHeight(480);
    m_view->setWidth(640);
    m_view->show();
    autoSignIn();
}

void AuthWindow::autoSignIn() {
    QString token;
    QJsonObject json;

    if (token = getToken(AuthToken); !token.isEmpty()) {
        json["type"] = AUTO_AUTH;
        json["token"] = token;
    } else if (token = getToken(AccessesToken); !token.isEmpty()) {
        json["type"] = AUTO_OAUTH;
        json["token"] = token;
    } else {
        return;
    }
    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void AuthWindow::response(const QString &response) {

    qDebug() << "Response is:\n" << response;

    auto json = QJsonDocument().fromJson(response.toUtf8()).object();
    if (!json.value("error").isNull()) {
        if (json.value("type").toInt() == AUTO_OAUTH) {
            m_googleAuth.refreshToken(getToken(RefreshToken));
        } else {
            // view error in ui
            QObject *object = m_view->rootObject();
            object->setProperty("error", true);
            object->setProperty("errorMessage", json.value("message"));
        }
        qDebug() << json.value("message");
    }
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

QString AuthWindow::getToken(const Type &type) {
    QFile file(AUTH_CONFIGURE_FILE);
    if (!file.open(QIODevice::ReadWrite)) {
        return "";
    }

    auto json = QJsonDocument().fromJson(file.readAll()).object();
    switch (type) {
    case AccessesToken:
        return json.value("accesses_token").toString();
    case AuthToken:
        return json.value("auth_token").toString();
    case RefreshToken:
        return json.value("refresh_token").toString();
    default: return "";
    }
}

void AuthWindow::saveTokens(const QString &accesses_token, const QString &refresh_token, const QString &auth_token = nullptr) {
    QFile file(AUTH_CONFIGURE_FILE);

    if (!file.open(QIODevice::ReadWrite)) {
        return;
    }

    QJsonObject json = QJsonDocument().fromJson(file.readAll()).object();
    if (!accesses_token.isNull())
        json["accesses_token"] = accesses_token;
    if (!refresh_token.isNull())
        json["refresh_token"] = refresh_token;
    if (!auth_token.isNull())
        json["auth_token"] = auth_token;

    QJsonDocument document;
    document.setObject(json);
    file.write(document.toJson(QJsonDocument::Indented));
}


