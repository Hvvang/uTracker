#include "responses.h"


Responses::Responses(Connection *ptr) {
    m_connection = ptr;
}

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

    m_connection->sendResponse(json);
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


    m_connection->sendResponse(json);
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

    m_connection->sendResponse(json);
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

    m_connection->sendResponse(json);
}