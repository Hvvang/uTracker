#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QObject>

#include "connection.h"


class AbstractRequestHandler : public QObject{
    Q_OBJECT
public:
    AbstractRequestHandler(Connection *connection);

    virtual void parseJSON(QJsonObject itemObject) = 0;

    signals:
    void responseInited(QJsonObject itemObject);

    public slots:
    virtual void responseSend(QJsonObject itemObject) = 0;

protected:
    Connection *m_connection;
    QByteArray m_json;
};

class ToSignUp : public AbstractRequestHandler {
    Q_OBJECT
public:
    ToSignUp(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class ToSignIn : public AbstractRequestHandler {
Q_OBJECT
public:
    ToSignIn(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};


class ToSignInWithGoogle : public AbstractRequestHandler {
Q_OBJECT
public:
    ToSignInWithGoogle(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class ToAutoSignIn : public AbstractRequestHandler {
Q_OBJECT
public:
    ToAutoSignIn(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class ToLogOut : public AbstractRequestHandler {
Q_OBJECT
public:
    ToLogOut(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

//class SendProfile : public AbstractRequestHandler {};
//class ToUpdateProfile : public AbstractRequestHandler {};
//
//class ToCreatedWorkflow : public AbstractRequestHandler {};
//class ToUpdateWorkflow : public AbstractRequestHandler {};
//class ToInvitedToWorkflow : public AbstractRequestHandler {};
//class SendAllWorkflows : public AbstractRequestHandler {};
//class SendSingleWorkflowData : public AbstractRequestHandler {};
//
//class sendStatistics : public AbstractRequestHandler {};