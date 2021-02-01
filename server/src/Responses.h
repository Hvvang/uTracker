#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

class Responses {
public:
    Responses(QTcpSocket *socket);
    ~Responses();

    void toSignUp(); // method for responsing to Signing Up
    void toSignIn(); // method for responsing to Signing In
    void toSignInWithGoogle(); // method for responsing to Signing In with Google
    void toAutoSignIn(); // method for responsing to Auto Signing In
//  void toLogOut();

//    void SendProfile();
////    void toUpdateProfile();

////    void toCreatedWorkflow();
////    void toUpdateWorkflow();
////    void toInvitedToWorkflow();

//    void sendAllWorkflows();
//    void sendSingleWorkflowData();

//    void sendStatistics();
private:
    QTcpSocket *m_socket;
};



//Responses *m_response = new Responses(socket);

//void Thread::parseJSON(QJsonDocument itemDoc) {
//    //parse
//    QJsonObject itemObject = itemDoc.object();
//    if (itemObject["type"].toString() == "SIGN_UP") {
//        qDebug() << "login :" << itemObject["login"].toString() << "\n";
//        qDebug() << "email :" << itemObject["email"].toString() << "\n";
//        qDebug() << "password :" << itemObject["password"].toString() << "\n";
//        qDebug() << "name :" << itemObject["name"].toString() << "\n";
//        qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
//        m_response->toSignUp();
//    }
//    else if (itemObject["type"].toString() == "SIGN_IN") {
//        qDebug() << "login :" << itemObject["login"].toString() << "\n";
//        qDebug() << "email :" << itemObject["email"].toString() << "\n";
//        qDebug() << "password :" << itemObject["password"].toString() << "\n";
//        m_response->toSignIn();
//    }
//    else if (itemObject["type"].toString() == "AUTO_OAUTH") {
//        qDebug() << "token :" << itemObject["token"].toString() << "\n";
//        m_response->toSignInWithGoogle();
//    }
//    else if (itemObject["type"].toString() == "AUTO_AUTH") {
//        qDebug() << "token :" << itemObject["token"].toString() << "\n";
//        m_response->toAutoSignIn();
//    }
//}

//void Thread::readyRead() {
//    // get the information
//    QByteArray Data = socket->readAll();
//
//    // will write on server side window
////    qDebug() << socketDescriptor << " Data in: " << Data;
//    // qDebug() << socketDescriptor << " Data:\n" << Data.toStdString().c_str();
//    QJsonDocument itemDoc = QJsonDocument::fromJson(Data);
//    if (itemDoc.isNull())
//        qDebug() << "ne json";
//    else
//        parseJSON(itemDoc);
//    //socket->write(Data);
//}

//        qDebug() << "login :" << itemObject["login"].toString() << "password :" << itemObject["password"].toString() << "\n";
//        QJsonArray itemArray = itemObject["array"].toArray();
//        for(auto item : itemArray)
//            qDebug() << item.toObject()["num"].toInt() << "\n";