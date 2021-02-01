#pragma once

#include <QRunnable>
#include <QTcpSocket>

#include "connection.h"

class Runnable : public QRunnable {
public:
    explicit Runnable(Connection *socket);

protected:
    void run() override;

private:
    Connection *m_ptr;
};
