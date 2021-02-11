#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QTcpSocket>

#include <QDataStream>

#include <iostream>

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

class AbstractRequest {

public:
    AbstractRequest(QTcpSocket *socket);

    void createJSON(QMap<QString, QVariant> map);
    void signUp(QString login, QString pass, QString name, QString surname, QString email);
    void signIn(QString email, QString  login, QString pass);
    void autoSignInWithGoogle(QString token);
    void autoSignIn(QString token);
    void logOut(int id);

    void createWorkflow(QString title, QString description, int ownerId);
    void updateWorkflow(QString title, QString description, int workflowId);
    void inviteToWorkflow(int userId, int workflowId);
    void getAllWorkflows(int userId);
    void getAllWorkflows();
    void getSingleWorkflowData(int workflowId);

    void getStatistics();

    void getProfile(int userId);
    void updateProfile(int userId, QString name, QString surname);
protected:
    QTcpSocket *m_socket;
};

class JsonFormat {

};