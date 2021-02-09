#pragma once

#include <QRunnable>
#include <QTcpSocket>

#include "responses.h"
#include "connection.h"

class Runnable : public QRunnable {
public:
    explicit Runnable(Connection *socket);
    ~Runnable() override;

    void parseJSON(QJsonDocument itemDoc);
    void setMutex(QMutex *mutex);
    void setTask(QByteArray task);

protected:
    void run() override;

private:
    QByteArray m_task;
    QMutex *m_mutex;
    Connection *m_ptr;

    AbstractRequestHandler *m_signUp;
    AbstractRequestHandler *m_signIn;
    AbstractRequestHandler *m_autoSignIn;
    AbstractRequestHandler *m_googleSignIn;
    AbstractRequestHandler *m_logOut;
    AbstractRequestHandler *m_createWorkFlow;
    AbstractRequestHandler *m_updateWorkFlow;
    AbstractRequestHandler *m_inviteToWorkFlow;
    AbstractRequestHandler *m_sendAllWorkFlows;
    AbstractRequestHandler *m_sendSingleWorkFlow;
    AbstractRequestHandler *m_sendStatistics;
    AbstractRequestHandler *m_sendProfile;
    AbstractRequestHandler *m_updateProfile;
};
