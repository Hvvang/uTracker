#include "runnable.h"

Runnable::Runnable(Connection *socket) {
    m_ptr = socket;
    m_response = new Responses(socket);
}

void Runnable::parseJSON(QJsonDocument itemDoc) {
    //parse
    QJsonObject itemObject = itemDoc.object();
    if (itemObject["type"].toString() == "SIGN_UP") {
        qDebug() << "login :" << itemObject["login"].toString() << "\n";
        qDebug() << "email :" << itemObject["email"].toString() << "\n";
        qDebug() << "password :" << itemObject["password"].toString() << "\n";
        qDebug() << "name :" << itemObject["name"].toString() << "\n";
        qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
        m_response->toSignUp();
    }
    else if (itemObject["type"].toString() == "SIGN_IN") {
        qDebug() << "login :" << itemObject["login"].toString() << "\n";
        qDebug() << "email :" << itemObject["email"].toString() << "\n";
        qDebug() << "password :" << itemObject["password"].toString() << "\n";
        m_response->toSignIn();
    }
    else if (itemObject["type"].toString() == "AUTO_OAUTH") {
        qDebug() << "token :" << itemObject["token"].toString() << "\n";
        m_response->toSignInWithGoogle();
    }
    else if (itemObject["type"].toString() == "AUTO_AUTH") {
        qDebug() << "token :" << itemObject["token"].toString() << "\n";
        m_response->toAutoSignIn();
    }
}

void Runnable::run() {
    QByteArray Data = m_ptr->getTask();;

    // will write on server side window
    // qDebug() << socketDescriptor << " Data in: " << Data;
    // qDebug() << socketDescriptor << " Data:\n" << Data.toStdString().c_str();
    QJsonDocument itemDoc = QJsonDocument::fromJson(Data);
    if (itemDoc.isNull())
        qDebug() << "ne json";
    else
        parseJSON(itemDoc);
    //socket->write(Data);
}


//      qDebug() << "login :" << itemObject["login"].toString() << "password :" << itemObject["password"].toString() << "\n";
//      QJsonArray itemArray = itemObject["array"].toArray();
//      for(auto item : itemArray)
//            qDebug() << item.toObject()["num"].toInt() << "\n";