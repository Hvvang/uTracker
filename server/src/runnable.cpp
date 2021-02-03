#include "runnable.h"

Runnable::Runnable(Connection *socket) {
    m_ptr = socket;
    m_signIn = new ToSignIn(socket);
    m_signUp = new ToSignUp(socket);
    m_autoSignIn = new ToAutoSignIn(socket);
    m_googleSignIn = new ToSignInWithGoogle(socket);
    m_logOut = new ToLogOut(socket);
}

void Runnable::parseJSON(QJsonDocument itemDoc) {
    if (true) {
        m_mutex->lock();
        qDebug() << "mutex locked";
        m_mutex->unlock();
    }
    else
        qDebug() << "mutex unlocked";

    QJsonObject itemObject = itemDoc.object();

    if (itemObject["type"].toString() == "SIGN_UP")
        emit m_signUp->responseInited(itemObject);
    else if (itemObject["type"].toString() == "SIGN_IN")
        emit m_signIn->responseInited(itemObject);
    else if (itemObject["type"].toString() == "AUTO_OAUTH")
        emit m_googleSignIn->responseInited(itemObject);
    else if (itemObject["type"].toString() == "AUTO_AUTH")
        emit m_autoSignIn->responseInited(itemObject);
    else if (itemObject["type"].toString() == "LOG_OUT")
        emit m_logOut->responseInited(itemObject);
}

Runnable::~Runnable() {
    delete m_signIn;
    delete m_signUp;
    delete m_autoSignIn;
    delete m_googleSignIn;
    delete m_logOut;
}

void Runnable::setMutex(QMutex *mutex) {
    m_mutex = mutex;
}

void Runnable::run() {
    qDebug() << m_ptr->getTask();
    return;

//    QJsonDocument itemDoc = QJsonDocument::fromJson(m_ptr->getTask());
//    if (!itemDoc.isNull())
//        parseJSON(itemDoc);
}
