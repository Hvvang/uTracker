#include "runnable.h"

Runnable::Runnable(Connection *socket) {
    m_ptr = socket;
    m_response = new Responses(m_ptr);
}

void Runnable::parseJSON(QJsonDocument itemDoc) {
    if (true) {
        m_mutex->lock();
        qDebug() << "mutex locked";
        m_mutex->unlock();
    }
    else
        qDebug() << "mutex unlocked";

    //parse
    QJsonObject itemObject = itemDoc.object();
    if (itemObject["type"].toString() == "SIGN_UP") {
        qDebug() << "login :" << itemObject["login"].toString() << "\n";
        qDebug() << "email :" << itemObject["email"].toString() << "\n";
        qDebug() << "password :" << itemObject["password"].toString() << "\n";
        qDebug() << "name :" << itemObject["name"].toString() << "\n";
        qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
        // DASHA TUT
        m_response->toSignUp();
    }
    else if (itemObject["type"].toString() == "SIGN_IN") {
        qDebug() << "login :" << itemObject["login"].toString() << "\n";
        qDebug() << "email :" << itemObject["email"].toString() << "\n";
        qDebug() << "password :" << itemObject["password"].toString() << "\n";
        //DASHA TUT
        m_response->toSignIn();
    }
    else if (itemObject["type"].toString() == "AUTO_OAUTH") {
        qDebug() << "token :" << itemObject["token"].toString() << "\n";
        //DASHA TUT
        m_response->toSignInWithGoogle();
    }
    else if (itemObject["type"].toString() == "AUTO_AUTH") {
        qDebug() << "token :" << itemObject["token"].toString() << "\n";
        //DASHA TUT
        m_response->toAutoSignIn();
    }
}

Runnable::~Runnable() {
    delete m_response;
}

void Runnable::setMutex(QMutex *mutex) {
    m_mutex = mutex;
}

void Runnable::run() {
    QJsonDocument itemDoc = QJsonDocument::fromJson(m_ptr->getTask());
    if (!itemDoc.isNull())
        parseJSON(itemDoc);
}

//      qDebug() << "login :" << itemObject["login"].toString() << "password :" << itemObject["password"].toString() << "\n";
//      QJsonArray itemArray = itemObject["array"].toArray();
//      for(auto item : itemArray)
//            qDebug() << item.toObject()["num"].toInt() << "\n";
