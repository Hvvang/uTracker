#include "Responses.h"


Responses::Responses(QTcpSocket *socket) : m_socket(socket) {}

Responses::~Responses() {}

void Responses::toSignUp() {
    QJsonObject jsonObject {
            {"type", "SIGN_UP"},
            {"message", "ebu sho pisat"}
    };
    if(true) { //have to b
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    m_socket->write(json);
}

void Responses::toSignIn() {
    QJsonObject jsonObject {
            {"type", "SIGN_IN"},
            {"message", "ebu sho pisat"}
    };
    if(true) { //have to b
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    m_socket->write(json);
}

void Responses::toSignInWithGoogle() {
    QJsonObject jsonObject {
            {"type", "AUTO_OAUTH"},
            {"message", "ebu sho pisat"}
    };
    if(true) { //have to b
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    m_socket->write(json);
}

void Responses::toAutoSignIn() {
    QJsonObject jsonObject {
            {"type", "AUTO_AUTH"},
            {"message", "ebu sho pisat"}
    };
    if(true) { //have to b
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    m_socket->write(json);
}