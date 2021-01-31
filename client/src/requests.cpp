#include "client.h"
#include "requests.h"

Request::Request(QTcpSocket *socket) : m_socket(socket) {};

void Request::signUp(){
    //creating json
    QString login = "ND";
    QString pass = "12345678";
    QJsonArray npcArray;
    QVector<int> vitya = {1, 2, 3, 4, 5};
    for (auto item : vitya) {
        QJsonObject npcObject {
            {"num", item}
        };
        npcArray.append(npcObject);
    }
    QJsonObject jsonObject {
        {"signup", true},
        {"login", login},
        {"password", pass},
        {"array", npcArray}
    };
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    qDebug() << "WANNA SIGNUP !";
    m_socket->write(json);
}

//    void Request::signIn(){}
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