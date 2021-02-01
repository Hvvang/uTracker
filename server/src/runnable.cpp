#include "runnable.h"

Runnable::Runnable(Connection *socket) {
    m_ptr = socket;
}

void Runnable::run() {
    qDebug() << m_ptr->getTask();
}