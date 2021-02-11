#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QSslSocket>

#include "requests.h"
#include "responsehandler.h"
#include "hash.h"


class Client: public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void doConnect(char *host, int port);

    void testConnect() const;
    void testRequestLoop();
    void parseJSON(QJsonDocument itemDoc);

public slots:
    void readyRead();
    void disconnected();
    void connectSuccess();
    void sslErrors(const QList<QSslError> &errors);
//    void encrypted();
//    void connected();
//    void socketError(QAbstractSocket::SocketError error);
//    void socketSslErrors(const QList &list);


private:
    std::shared_ptr<QSslSocket> m_ssl_socket;
    std::unique_ptr<AbstractRequest> m_request;
    std::shared_ptr<AbstractResponseHandler> m_signUp;
    std::shared_ptr<AbstractResponseHandler> m_signIn;
    std::shared_ptr<AbstractResponseHandler> m_autoSignIn;
    std::shared_ptr<AbstractResponseHandler> m_googleSignIn;
    std::shared_ptr<AbstractResponseHandler> m_logOut;
    std::shared_ptr<AbstractResponseHandler> m_createdWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_updateWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_inviteToWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_allWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_singleWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_sendStat;
    std::shared_ptr<AbstractResponseHandler> m_sendProfile;
    std::shared_ptr<AbstractResponseHandler> m_updateProfile;

    bool configSSL();

    void reconnect();  // implement reconnection when break
};