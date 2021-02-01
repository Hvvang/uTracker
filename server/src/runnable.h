#pragma once

#include <QRunnable>
#include <QTcpSocket>

#include "Responses.h"

class Runnable : public QRunnable {
public:
    explicit Runnable(Connection *socket);
    void parseJSON(QJsonDocument itemDoc);

protected:
    void run() override;

private:
    Connection *m_ptr;
    Responses *m_response;
};
