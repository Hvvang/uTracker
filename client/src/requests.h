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

    virtual QByteArray createJSON(QByteArray data) = 0;

    void send();

protected:
    QTcpSocket *m_socket;
    QByteArray m_json;
};


class signUp : public AbstractRequest {
public:
    signUp(QTcpSocket *socket, QByteArray data);
    QByteArray createJSON(QByteArray data);
};

class signIn : public AbstractRequest {
    public:
    signIn(QTcpSocket *socket, QByteArray data);
    QByteArray createJSON(QByteArray data);
};

class autoSignInWithGoogle : public AbstractRequest {
    public:
    autoSignInWithGoogle(QTcpSocket *socket, QByteArray data);
    QByteArray createJSON(QByteArray data);
};

class autoSignIn : public AbstractRequest {
    public:
    autoSignIn(QTcpSocket *socket, QByteArray data);
    QByteArray createJSON(QByteArray data);
};

// class logOut : public AbstractRequest {
//  public:
//     signUp(QTcpSocket *socket, QByteArray data);
//     QByteArray createJSON(QByteArray data);
// };
// /////////////////////////////////////////
// class getProfile : public AbstractRequest {};
// class updateProfile : public AbstractRequest {};
// //////////////////////////////////////////
// class createWorkflow: public AbstractRequest {};
// class updateWorkflow: public AbstractRequest {};
// class inviteToWorkflow: public AbstractRequest {};
// class getAllWorkflows: public AbstractRequest {};
// class getSingleWorkflowData: public AbstractRequest {};
// /////////////////////////////////////////////////
// class getStatistics : public AbstractRequest {};
