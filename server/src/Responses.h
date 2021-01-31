#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

class Responses {
public:
    Responses(QTcpSocket *socket);
    ~Responses();

    void toSignUp();
//    void toSignIn();
//    void toLogOut();
//
//    void SendProfile();
////    void toUpdateProfile();
//
////    void toCreatedWorkflow();
////    void toUpdateWorkflow();
////    void toInvitedToWorkflow();
//
//    void sendAllWorkflows();
//    void sendSingleWorkflowData();
//
//    void sendStatistics();
private:
    QTcpSocket *m_socket;
};


