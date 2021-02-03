#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QTcpSocket>

#include <QDataStream>

#include <iostream>

class AbstractRequest {

public:
    AbstractRequest(QTcpSocket *socket);

    void createJSON(QMap<QString, QVariant> map);
    void signUp(QString login, QString pass, QString name, QString surname, QString email);
    void signIn(QString email, QString  login, QString pass);
    void autoSignInWithGoogle(QString token);
    void autoSignIn(QString token);
    void logOut();

//    void getProfile(QMap<QString, QVariant> map);
//    void updateProfile(QMap<QString, QVariant> map);
//    void createWorkflow(QMap<QString, QVariant> map);
//    void updateWorkflow(QMap<QString, QVariant> map);
//    void inviteToWorkflow(QMap<QString, QVariant> map);
//    void getAllWorkflows(QMap<QString, QVariant> map);
//    void getSingleWorkflowData(QMap<QString, QVariant> map);
//    void getStatistics(QMap<QString, QVariant> map);

protected:
    QTcpSocket *m_socket;
};

class JsonFormat {

};