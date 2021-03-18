//
// Created by Artem Shemidko on 02.02.2021.
//

#ifndef UTRACKER_ABSTRACTRESPONSEHANDLER_H
#define UTRACKER_ABSTRACTRESPONSEHANDLER_H

#include <QObject>

enum class ResponseType {
    SIGN_UP = 0,
    SIGN_IN = 1,
    AUTO_OAUTH = 2,
    AUTO_AUTH = 3,
    LOG_OUT = 4,

    CREATE_WORKFLOW = 5,
    ARCHIVE_WORKFLOW = 6,
    UPDATE_WORKFLOW = 7,
    INVITE_CONTACT = 8,

    GET_WORKFLOW_COLABORANTS = 10,
    GET_WORKFLOWS = 11,

    PROFILE = 14,

    GET_PANEL = 16,
    RENAME_PANEL = 17,
    GET_WORKFLOW_PANELS = 18,
    REMOVE_PANEL = 19,
    GET_TASK = 20,
    GET_PANEL_TASKS = 21,
    UPDATE_TASK_TITLE = 22,
    UPDATE_TASK = 23,
    MOVE_TASK = 24,
    REMOVE_TASK = 25,
    GET_TASK_DATA = 26,

    GET_TASKS_WORKERS = 27,
    GET_WORK_STATUS = 28,
    GET_TASK_WORKER = 29,
    REMOVE_TASK_WORKER = 30,
    GET_TASK_DONE_STATUS = 31,

    GET_DAILY_PLAN = 40,
    ADD_DAILY_TASK = 41,
    REMOVE_DAILY_TASK = 42,
    UPDATE_DAILY_TASK = 43,
    RESET_DAILY_PLAN = 44,

    ERROR = 250,
};

class AbstractResponseHandler : public QObject {
Q_OBJECT
public:

    enum class ResponseErrorType {
        NoError = 200,
        NotValid = 1,
        BadToken,
    };

    explicit AbstractResponseHandler(QObject *parent = nullptr);

    ResponseType type(const QByteArray &data);
    ResponseErrorType error(const QByteArray &data);
    QString handleMessage(const QByteArray &data);

    virtual void processResponse(const QByteArray &data) = 0;

signals:
    void auth(const QByteArray &);
    void profile(const QByteArray &);
    void newWorkflow(const QByteArray &);
    void archiveWorkflow(const QByteArray &);
    void inviteContact(const QByteArray &);
    void getWorkflows(const QByteArray &);
    void updateWorkflow(const QByteArray &);
    void getWorkflowColaborants(const QByteArray &);
    void getWorkflowPanels(const QByteArray &);
    void getPanelTasks(const QByteArray &);
    void getTaskWorkers(const QByteArray &);
    void getTask(const QByteArray &);
    void getTaskDescription(const QByteArray &);
    void getPanel(const QByteArray &);
    void renamePanel(const QByteArray &);
    void renameTask(const QByteArray &);
    void updateTask(const QByteArray &);
    void moveTask(const QByteArray &);
    void removeTask(const QByteArray &);
    void getWorkStatus(const QByteArray &);
    void getTaskWorker(const QByteArray &);
    void removeTaskWorker(const QByteArray &);
    void getTaskDoneStatus(const QByteArray &);

    void getDailyPlan(const QByteArray &);
    void resetDailyPlan(const QByteArray &);
    void getDailyPlanTask(const QByteArray &);
    void removeDailyPlanTask(const QByteArray &);
    void updateDailyPlanTask(const QByteArray &);



private slots:
    void mediator(const QByteArray &);

};


#endif //UTRACKER_ABSTRACTRESPONSEHANDLER_H
