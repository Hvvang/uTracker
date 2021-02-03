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

    QVector<AbstractRequestHandler *> funcList;
    funcList.append({m_signUp, m_signIn, m_autoSignIn, m_googleSignIn, m_logOut});
    QStringList list;
    list << "SIGN_UP" << "SIGN_IN" << "AUTO_AUTH" << "AUTO_OAUTH" << "LOG_OUT";
    for (auto i : list)
        if (i == itemObject["type"].toString())
            emit funcList[list.indexOf(i)]->responseInited(itemObject);
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

void Runnable::setTask(QByteArray task) {
    m_task = task;
}

void Runnable::run() {
    QJsonDocument itemDoc = QJsonDocument::fromJson(m_task);
    if (!itemDoc.isNull())
        parseJSON(itemDoc);
}
