#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include "connection.h"

class Responses {
public:
    Responses(Connection *ptr);

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
    Connection *m_connection;
};
