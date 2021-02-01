#pragma once

#include <QRunnable>
#include <QTcpSocket>
#include <QMutex>

#include "Responses.h"

class Runnable : public QRunnable {
public:
    explicit Runnable(Connection *socket);
    void parseJSON(QJsonDocument itemDoc);

    void setMutex(QMutex *mutex);

protected:
    void run() override;

private:
    QMutex *m_mutex;
    Connection *m_ptr;
    Responses *m_response;
};
