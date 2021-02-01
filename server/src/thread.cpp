#include "thread.h"

Thread::Thread(qintptr ID, QObject *parent) : QThread(parent) {
    this->socketDescriptor = ID;
    socket = nullptr;
}

void Thread::run() {
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();
    m_response = new Responses(socket);

    // set the ID
    if (!socket->setSocketDescriptor(this->socketDescriptor)) {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multiThreaded
    // This makes the slot to be invoked immediately, when the signal is emitted.
    connect(socket, &QTcpSocket::readyRead, this, &Thread::readyRead, Qt::DirectConnection);
    connect(socket, &QTcpSocket::disconnected, this, &Thread::disconnected);

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies
    exec();
}

void Thread::parseJSON(QJsonDocument itemDoc) {
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


void Thread::readyRead() {
    // get the information
    QByteArray Data = socket->readAll();

    // will write on server side window
//    qDebug() << socketDescriptor << " Data in: " << Data;
    // qDebug() << socketDescriptor << " Data:\n" << Data.toStdString().c_str();
    QJsonDocument itemDoc = QJsonDocument::fromJson(Data);
    if (itemDoc.isNull())
        qDebug() << "ne json";
    else
        parseJSON(itemDoc);
    //socket->write(Data);
}

void Thread::disconnected() {
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
