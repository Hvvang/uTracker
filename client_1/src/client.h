#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

#include "requests.h"
#include "responsehandler.h"
#include "hash.h"


class Client: public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client() override;

    void doConnect(char *ip, int port);
    void testRequestLoop();
    void parseJSON(QJsonDocument itemDoc);

signals:

public slots:
    void disconnected();
    void readyRead();

private:
    QTcpSocket *m_socket;
    AbstractRequest *m_request;

    AbstractResponseHandler *m_signUp;
    AbstractResponseHandler *m_signIn;
    AbstractResponseHandler *m_autoSignIn;
    AbstractResponseHandler *m_googleSignIn;
    AbstractResponseHandler *m_logOut;
    AbstractResponseHandler *m_createdWorkflow;
    AbstractResponseHandler *m_updateWorkflow;
    AbstractResponseHandler *m_inviteToWorkflow;
    AbstractResponseHandler *m_allWorkflow;
    AbstractResponseHandler *m_singleWorkflow;
    AbstractResponseHandler *m_sendStat;
    AbstractResponseHandler *m_sendProfile;
    AbstractResponseHandler *m_updateProfile;
};