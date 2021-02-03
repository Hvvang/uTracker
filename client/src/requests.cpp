#include "client.h"
#include "requests.h"

AbstractRequest::AbstractRequest(QTcpSocket *socket) : m_socket(socket) {}

void AbstractRequest::createJSON(QMap<QString, QVariant> map) {

    QJsonObject jsonObject =  QJsonObject::fromVariantMap(map);
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    qDebug() << json;
    m_socket->write(json);
}

void AbstractRequest::signUp(QString login, QString pass, QString name, QString surname, QString email) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = "SIGN_UP";
    mapa["login"] = login;
    mapa["password"] = pass;
    mapa["email"] = email;
    mapa["name"] = name;
    mapa["surname"] = surname;
    createJSON(mapa);
}
void AbstractRequest::signIn(QString email, QString  login, QString pass) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = "SIGN_IN";
    mapa["login"] = login;
    mapa["password"] = pass;
    mapa["email"] = email;
    createJSON(mapa);
}
void AbstractRequest::autoSignInWithGoogle(QString token) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = "AUTO_OAUTH";
    mapa["token"] = token;
    createJSON(mapa);
}
void AbstractRequest::autoSignIn(QString token) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = "AUTO_AUTH";
    mapa["token"] = token;
    createJSON(mapa);
}
void AbstractRequest::logOut() {
    QMap<QString, QVariant> mapa;
    mapa["type"] = "LOG_OUT";
    createJSON(mapa);
}

// //EXAMPLE
// //creating json
// //QString login = "ND";
// //QString pass = "12345678";
// //QJsonArray npcArray;
// //QVector<int> vitya = {1, 2, 3, 4, 5};
// //for (auto item : vitya) {
// //QJsonObject npcObject {
// //        {"num", item}
// //};
// //npcArray.append(npcObject);
// //}
// //QJsonObject jsonObject {
// //        {"type", "signup"},
// //        {"login", login},
// //        {"password", pass},
// //        {"array", npcArray}
// //};
// //QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
// //QByteArray json = jsonDoc->toJson();
// //qDebug() << "WANNA SIGNUP !";
// //m_socket->write(json);