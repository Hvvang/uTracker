#include "client.h"
#include "requests.h"

Request::Request(QTcpSocket *socket) : m_socket(socket) {};

//EXAMPLE
//creating json
//QString login = "ND";
//QString pass = "12345678";
//QJsonArray npcArray;
//QVector<int> vitya = {1, 2, 3, 4, 5};
//for (auto item : vitya) {
//QJsonObject npcObject {
//        {"num", item}
//};
//npcArray.append(npcObject);
//}
//QJsonObject jsonObject {
//        {"type", "signup"},
//        {"login", login},
//        {"password", pass},
//        {"array", npcArray}
//};
//QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
//QByteArray json = jsonDoc->toJson();
//qDebug() << "WANNA SIGNUP !";
//m_socket->write(json);

void Request::signUp(){
    //creating json
    QString login = "ND";
    QString pass = "12345678";
    QString email = "lala@gmail.com";
    QString name = "Nazar";
    QString surname = "Dykyy";

    QJsonObject jsonObject {
            {"type", "SIGN_UP"},
            {"email", email},
            {"password", pass}, // SHA-256 hash,
            {"login", login},
            {"name", name},
            {"surname", surname}
    };

    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    qDebug() << "WANNA signUp() !";
    m_socket->write(json);
}

void Request::signIn(){
    //creating json
    QString login = "ND";
    QString pass = "12345678";
    QString email = "lala@gmail.com";

    QJsonObject jsonObject {
            {"type", "SIGN_IN"},
            {"email", email},
            {"password", pass}, // SHA-256 hash,
            {"login", login},
    };

    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    qDebug() << "WANNA signIn() !";
    m_socket->write(json);
}

void Request::autoSignInWithGoogle() {
    //creating json
    QString token = "12345678";

    QJsonObject jsonObject {
            {"type", "AUTO_OAUTH"},
            {"token", token} // SHA-256 hash,

    };

    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    qDebug() << "WANNA autoSignInWithGoogle() !";
    m_socket->write(json);
}

void Request::autoSignIn() {
    //creating json
    QString token = "12345678";

    QJsonObject jsonObject {
            {"type", "AUTO_AUTH"},
            {"token", token} // SHA-256 hash,

    };

    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    qDebug() << "WANNA autoSignIn() !";
    m_socket->write(json);
}

//    void Request::logOut(){}
//
//    void Request::getProfile(){}
//    void Request::updateProfile(){}
//
//    void Request::updateWorkflow(){}
//    void Request::inviteToWorkflow(){}
//    void Request::getAllWorkflows(){}
//    void Request::getSingleWorkflowData(){}
//
//    void Request::getStatistics(){}