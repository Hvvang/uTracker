#include "runnable.h"

Runnable::Runnable(Connection *socket) {
    m_ptr = socket;
}

void Runnable::setMutex(QMutex *mutex) {
    m_mutex = mutex;
}

void Runnable::run() {
    if (true) {
        m_mutex->lock();
        qDebug() << "mutex locked";
        m_mutex->unlock();
    }
    else
        qDebug() << "mutex unlocked";
    qDebug() << m_ptr->getTask();
}