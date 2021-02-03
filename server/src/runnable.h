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

protected:
    void run() override;

private:
    QMutex *m_mutex;
    Connection *m_ptr;
    ToSignUp *m_signUp;
    ToSignIn *m_signIn;
    ToAutoSignIn *m_autoSignIn;
    ToSignInWithGoogle *m_googleSignIn;
    ToLogOut *m_logOut;
};
