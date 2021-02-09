#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QObject>

#include "connection.h"

enum class RequestType {
    SIGN_UP,
    SIGN_IN,
    AUTO_AUTH,
    AUTO_OAUTH,
    LOG_OUT,
    CREATE_WORKFLOW,
    UPDATE_WORKFLOW,
    INVITE_TO_WORKFLOW,
    GET_ALL_WORKFLOWS,
    GET_SINGLE_WORKFLOW_DATA,
    GET_STATISTICS,
    GET_PROFILE,
    UPDATE_PROFILE
};

class SendResp : public QObject{
    Q_OBJECT
public:
    SendResp(Connection *connection);

public slots:
    void getAnswer(const QMap<QString, QVariant> &mapa);
protected:
    Connection *m_connection;
    QByteArray m_json;
};

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

class ToCreatedWorkflow : public AbstractRequestHandler {
Q_OBJECT
public:
    ToCreatedWorkflow(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class ToUpdateWorkflow : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToUpdateWorkflow(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class ToInvitedToWorkflow : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToInvitedToWorkflow(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class SendAllWorkflows : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendAllWorkflows(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class SendSingleWorkflowData : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendSingleWorkflowData(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class SendStatistics : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendStatistics(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class SendProfile : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendProfile(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

class ToUpdateProfile : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToUpdateProfile(Connection *socket);
    void parseJSON(QJsonObject itemObject);

public slots:
    void responseSend(QJsonObject itemObject);
};

