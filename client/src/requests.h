#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <iostream>

class Request {

public:
    Request(QTcpSocket *socket);

    void signUp();
    void signIn();
    void autoSignInWithGoogle();
    void autoSignIn();
//    void logOut();
//
//    void getProfile();
//    void updateProfile();
//
//    void createWorkflow();
//    void updateWorkflow();
//    void inviteToWorkflow();
//    void getAllWorkflows();
//    void getSingleWorkflowData();
//
//    void getStatistics();

private:
    QTcpSocket *m_socket;
};
