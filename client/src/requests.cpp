#include "client.h"
#include "requests.h"

AbstractRequest::AbstractRequest(QTcpSocket *socket) : m_socket(socket) {}

void AbstractRequest::send() {
    m_socket->write(m_json);
}

signUp::signUp(QTcpSocket *socket, QByteArray data) : AbstractRequest(socket) {
    m_json = createJSON(data);
}

QByteArray signUp::createJSON(QByteArray data) {
    QDataStream r_stream(&data, QIODevice::ReadOnly);
    QString test;
    QJsonObject jsonObject {
        {"type", "SIGN_UP"}
    };
    r_stream >> test;
    jsonObject["email"] = test;
    r_stream >> test;
    jsonObject["password"] = test;// SHA-256 hash,
    r_stream >> test;
    jsonObject["login"] = test;
    r_stream >> test;
    jsonObject["name"] = test;
    r_stream >> test;
    jsonObject["surname"] = test;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    return jsonDoc->toJson();
}

signIn::signIn (QTcpSocket *socket, QByteArray data) : AbstractRequest(socket) {
    m_json = createJSON(data);
}


QByteArray signIn::createJSON(QByteArray data) {
    QDataStream r_stream(&data, QIODevice::ReadOnly);
    QString test;
    QJsonObject jsonObject {
        {"type", "SIGN_IN"}
    };
    r_stream >> test;
    jsonObject["email"] = test;
    r_stream >> test;
    jsonObject["password"] = test;// SHA-256 hash,
    r_stream >> test;
    jsonObject["login"] = test;

    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    return jsonDoc->toJson();
}

autoSignInWithGoogle::autoSignInWithGoogle (QTcpSocket *socket, QByteArray data) : AbstractRequest(socket) {
    m_json = createJSON(data);
}

QByteArray autoSignInWithGoogle::createJSON(QByteArray data) {
    QDataStream r_stream(&data, QIODevice::ReadOnly);
    QString test;
    QJsonObject jsonObject {
        {"type", "AUTO_OAUTH"}
    };
    r_stream >> test;
    jsonObject["token"] = test;

    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    return jsonDoc->toJson();
}

autoSignIn::autoSignIn (QTcpSocket *socket, QByteArray data) : AbstractRequest(socket) {
    m_json = createJSON(data);
}

QByteArray autoSignIn::createJSON(QByteArray data) {
    QDataStream r_stream(&data, QIODevice::ReadOnly);
    QString test;
    QJsonObject jsonObject {
        {"type", "AUTO_AUTH"}
    };
    r_stream >> test;
    jsonObject["token"] = test;

    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    return jsonDoc->toJson();
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