#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QObject>

class AbstractResponseHandler : public QObject {
Q_OBJECT
public:
    AbstractResponseHandler(std::shared_ptr<QSslSocket> socket);

signals:
    void handleInited(QJsonObject itemObject);

public slots:
    virtual void responseHandle(QJsonObject itemObject) = 0;

protected:
    std::shared_ptr<QSslSocket>  m_socket;
    QByteArray m_json;
};

class SignUpResponse : public AbstractResponseHandler {
Q_OBJECT

public:
    SignUpResponse(std::shared_ptr<QSslSocket> socket);

public slots:
    void responseHandle(QJsonObject itemObject);
};

class SignInResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignInResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SignInWithGoogleResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignInWithGoogleResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class AutoSignInResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    AutoSignInResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class LogOutResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    LogOutResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class CreatedWorkflowResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    CreatedWorkflowResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class UpdateWorkflowResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    UpdateWorkflowResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class InvitedToWorkflowResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    InvitedToWorkflowResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class AllWorkflowsResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    AllWorkflowsResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SingleWorkflowDataResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SingleWorkflowDataResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendStatistics : public AbstractResponseHandler {
Q_OBJECT
public:
    SendStatistics(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendProfileResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SendProfileResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToUpdateProfileResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    ToUpdateProfileResponse(std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};
