#include <sys/socket.h>
#include "responses.h"

AbstractRequestHandler::AbstractRequestHandler(Connection *connection) : m_connection(connection) {
    connect(this, &AbstractRequestHandler::responseInited, &AbstractRequestHandler::responseSend);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignUp::ToSignUp(Connection *socket) :  AbstractRequestHandler(socket){}

void ToSignUp::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    Q_UNUSED(itemObject);
    QJsonObject jsonObject {
            {"type", "SIGN_UP"},
            {"message", "ebu sho pisat"}
    };
    if(true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToSignUp::parseJSON(QJsonObject itemObject){
    qDebug() << "login :" << itemObject["login"].toString() << "\n";
    qDebug() << "email :" << itemObject["email"].toString() << "\n";
    qDebug() << "password :" << itemObject["password"].toString() << "\n";
    qDebug() << "name :" << itemObject["name"].toString() << "\n";
    qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
    // DASHA TUT
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignIn::ToSignIn(Connection *socket) : AbstractRequestHandler(socket){}

void ToSignIn::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", "SIGN_IN"},
            {"message", "ebu sho pisat"}
    };
    if(true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToSignIn::parseJSON(QJsonObject itemObject) {
    qDebug() << "login :" << itemObject["login"].toString() << "\n";
    qDebug() << "email :" << itemObject["email"].toString() << "\n";
    qDebug() << "password :" << itemObject["password"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignInWithGoogle::ToSignInWithGoogle(Connection *socket) : AbstractRequestHandler(socket){}

void ToSignInWithGoogle::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", "AUTO_OAUTH"},
            {"message", "ebu sho pisat"}
    };
    if(true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    m_connection->sendResponse(json);
}

void ToSignInWithGoogle::parseJSON(QJsonObject itemObject) {
        qDebug() << "token :" << itemObject["token"].toString() << "\n";
        //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToAutoSignIn::ToAutoSignIn(Connection *socket) : AbstractRequestHandler(socket){}

void ToAutoSignIn::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", "AUTO_AUTH"},
            {"message", "ebu sho pisat"}
    };
    if(true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToAutoSignIn::parseJSON(QJsonObject itemObject) {
    qDebug() << "token :" << itemObject["token"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToLogOut::ToLogOut(Connection *socket) : AbstractRequestHandler(socket){}

void ToLogOut::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", "LOG_OUT"}
    };
    if(true)
        jsonObject["message"] = "Succesfull";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToLogOut::parseJSON(QJsonObject itemObject) {
    qDebug() << "userId :" << itemObject["userId"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////