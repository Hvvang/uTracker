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
    Connection *m_connection;

    std::shared_ptr<AbstractRequestHandler> m_signUp;
    std::shared_ptr<AbstractRequestHandler> m_signIn;
    std::shared_ptr<AbstractRequestHandler> m_autoSignIn;
    std::shared_ptr<AbstractRequestHandler> m_googleSignIn;
    std::shared_ptr<AbstractRequestHandler> m_logOut;
    std::shared_ptr<AbstractRequestHandler> m_createWorkFlow;
    std::shared_ptr<AbstractRequestHandler> m_archiveWorkFlow;
    std::shared_ptr<AbstractRequestHandler> m_updateWorkFlow;
    std::shared_ptr<AbstractRequestHandler> m_inviteToWorkFlow;
    std::shared_ptr<AbstractRequestHandler> m_removeFromWorkFlow;
    std::shared_ptr<AbstractRequestHandler> m_getUsersFromWorkFlow;
    std::shared_ptr<AbstractRequestHandler> m_sendAllWorkFlows;
    std::shared_ptr<AbstractRequestHandler> m_sendSingleWorkFlow;
    std::shared_ptr<AbstractRequestHandler> m_sendStatistics;
    std::shared_ptr<AbstractRequestHandler> m_sendProfile;
    std::shared_ptr<AbstractRequestHandler> m_updateProfile;
    std::shared_ptr<AbstractRequestHandler> m_createList;
    std::shared_ptr<AbstractRequestHandler> m_renameList;
    std::shared_ptr<AbstractRequestHandler> m_getLists;
    std::shared_ptr<AbstractRequestHandler> m_removeList;
    std::shared_ptr<AbstractRequestHandler> m_createTask;
    std::shared_ptr<AbstractRequestHandler> m_getTasks;
    std::shared_ptr<AbstractRequestHandler> m_updateTaskTitleRequestHandler;
    std::shared_ptr<AbstractRequestHandler> m_updateTask;
    std::shared_ptr<AbstractRequestHandler> m_moveTask;
    std::shared_ptr<AbstractRequestHandler> m_removeTask;
    std::shared_ptr<AbstractRequestHandler> m_sendTaskData;
    std::shared_ptr<AbstractRequestHandler> m_changeTaskWorkStatus;
    std::shared_ptr<AbstractRequestHandler> m_changeTaskDoneStatus;
    std::shared_ptr<AbstractRequestHandler> m_getTaskWorkers;

    std::shared_ptr<AbstractRequestHandler> m_getDailyPlan;
    std::shared_ptr<AbstractRequestHandler> m_createDailyTask;
    std::shared_ptr<AbstractRequestHandler> m_removeDailyTask;
    std::shared_ptr<AbstractRequestHandler> m_updateDailyTask;

};
