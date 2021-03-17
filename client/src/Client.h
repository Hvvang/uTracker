//
// Created by Artem Shemidko on 03.02.2021.
//

#ifndef UTRACKER_CLIENT_H
#define UTRACKER_CLIENT_H


#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QQuickItem>

#include "googleauth.h"


// MODELS
#include "WorkflowsModel.h"
#include "KanbanModel.h"
#include "TaskDescriptionModel.h"


// RESPONSE HANDLERS
#include "AuthorisationResponseHandler.h"
#include "ProfileDataResponseHandler.h"
#include "CreateWorkflowResponseHandler.h"
#include "ArchiveWorkflowResponseHandler.h"
#include "InviteContactResponseHandler.h"
#include "GetWorkflowsResponseHandler.h"
#include "EditWorkflowResponseHandler.h"
#include "GetWorkflowColaborantsResponseHandler.h"
#include "GetWorkflowPanelsResponseHandler.h"
#include "GetPanelTasksResponseHandler.h"
#include "GetTaskWorkersResponseHandler.h"
#include "GetTaskResponseHandler.h"
#include "GetPanelResponseHandler.h"
#include "RenamePanelTitleResponseHandler.h"
#include "GetTaskTitleUpdatingResponseHandler.h"
#include "GetTaskDescriptionResponseHandler.h"
#include "GetTaskUpdatingResponseHandler.h"
#include "MoveTaskResponseHandler.h"
#include "RemoveTaskResponseHandler.h"
#include "GetWorkStatusResponseHandler.h"
#include "GetTaskWorkerResponseHandler.h"
#include "RemoveTaskWorkerResponseHandler.h"
#include "GetTaskDoneStatusResponseHandler.h"


#define AUTH_CONFIGURE_FILE QCoreApplication::applicationDirPath() + "/.auth_config"

#define UI_AuthWindow "qrc:/qml/authwindow/Authorization.qml"
#define UI_MainWindow "qrc:/qml/mainwindow/Mainwindowview.qml"

#define ENUM_TO_INT(var) static_cast<int>(var)

struct Profile {
    int id;
    QString login = "";
    QString name = "";
    QString surname = "";
};

class Client: public QObject {
Q_OBJECT
    Q_PROPERTY(QChar letter READ nameFirstLetter NOTIFY profileNameChanged)
public:
    enum class Ui {
        Root,
        WorkFlows,
        DailyPlane,
        Contacts,
        Calendar,
        Statistic,
        Kanban,
    };

    enum class RequestType {
        SIGN_UP = 0,
        SIGN_IN = 1,
        AUTO_AUTH = 2,
        AUTO_OAUTH = 3,
        LOGOUT = 4,
        CREATE_WORKFLOW = 5,
        ARCHIVE_WORKFLOW = 6,
        UPDATE_WORKFLOW = 7,
        INVITE_CONTACT = 8,

        GET_WORKFLOW_COLABORANT = 10,
        GET_WORKFLOWS = 11,

        GET_STATISTICS = 13,

        GET_PROFILE = 14,
        UPDATE_PROFILE = 15,


        CREATE_PANEL = 16,
        RENAME_PANEL = 17,
        GET_WORKFLOW_PANELS = 18,
        REMOVE_PANEL = 19,
        CREATE_TASK = 20,
        GET_PANEL_TASKS = 21,
        UPDATE_TASK_TITLE = 22,
        UPDATE_TASK = 23,
        MOVE_TASK = 24,
        REMOVE_TASK = 25,
        GET_TASK_DATA = 26,
        GET_TASK_WORKERS = 27,
        NOTE_WORK_STATUS = 28,
        GET_TASK_WORKER = 29,
        REMOVE_TASK_WORKER = 30,
        NOTE_TASK_DONE_STATUS = 31,

    };

    Client(QQmlApplicationEngine *engine = nullptr, const QHostAddress &host = QHostAddress::LocalHost,
           const quint16 port = 5000, QObject *parent = nullptr);

    Profile &profile();
    void initResponseHandlers();
    void deInitResponseHandlers();
    void saveToken(const QString &type, const QString &value);
    QString getToken(const QString &type);
    static Client* singleton();
    static QQmlApplicationEngine* engineSingleton();

    void initWorkflowsModel();
    void getProfileData();

    void setProfile(const QString &login, const QString &name, const QString &surname);
    void setId(quint64 m_id);

    void autoSignIn();

    QChar nameFirstLetter();
    void newWorkflow(const Workflow &flow);

    void removeWorkflow(int index);
    void addColaborant(quint64 flowIndex, const Colaborant &contact);
    void updateWorkflow(const Workflow &flow);
    void getWorkflowColaborants(int workflowId);
    void getTaskWorkers(const int &taskId);
    void getPanelTasks(int panelId);
    void addPanel(const int &workflowId, const Kanban &kanban);
    void renamePanel(const int &workflowId, const int &panelIndex, const QString &title);
    void renameTask(const int &taskId, const int &panelId, const QString &title);
    void updateTaskPreview(const int &taskId, const int &panelId, const QString &title, const QStringList &tags);
    void updateTaskIndex(const int &taskId, const int &fromPanel, const int &fromIndex, const int &toPanel, const int &toIndex);
    void populateTaskModel(const int &taskId, const QString &title, const QString &creation_time,
                           const QString &deadline_time, const QStringList &tags, const QString &description);

    void addTask(const int &panelId, const Task &task);
    void deleteTask(const int &panelId, const int &taskId);
    void setTaskWorkStatus(const int &panelId, const int &taskId, const bool &status);
    void setTaskDoneStatus(const int &panelId, const int &taskId, const bool &status);
    void addWorker(const int &panelId, const int &taskId, const Colaborant &worker);
    void removeWorker(const int &panelId, const int &taskId, const int &workerId);

    void reject();

    Q_INVOKABLE void googleAuthorize();
    Q_INVOKABLE void authorize(const QString &email, const QString &password);
    Q_INVOKABLE void registrate(const QString &email, const QString &password, const QString &name, const QString &surname);
    Q_INVOKABLE void getWorkflows();
    Q_INVOKABLE void openWorkflow(int wokflowId);
    Q_INVOKABLE void createWorkflow(const QString &title, const QString &date);
    Q_INVOKABLE void archiveWorkflow(int index);
    Q_INVOKABLE void inviteContact(const QString &contact, int index);
    Q_INVOKABLE void editWorkflow(int index, const QString &title, const QString &date);
    Q_INVOKABLE void newTask(const int &panelId, const int &taskIndex);
    Q_INVOKABLE void newPanel(const int &workflowId, const int &panelIndex);
    Q_INVOKABLE void updatePanelTitle(const int &panelId, const QString &title);
    Q_INVOKABLE void updateTaskTitle(const int &taskId, const QString &title);
    Q_INVOKABLE void getTaskDescription(const int &taskId);
    Q_INVOKABLE void finishEditingTask();
    Q_INVOKABLE void moveTask(const int &taskId, const int &panelId, const int &index);
    Q_INVOKABLE void removeTask(const int &taskId);
    Q_INVOKABLE void noteTaskWorkStatus(const int &taskId, const bool &status);
    Q_INVOKABLE void noteTaskDoneStatus(const int &taskId, const bool &status);
    Q_INVOKABLE void logout();


protected:
    static Client* m_instance;
    static QQmlApplicationEngine *m_qmlEngine;

private:
    bool updateKanbanModelIfNeeded(int workflowId);
    bool updateTaskModelIfNeeded(const int &taskId);

signals:
    void notification(const QString &msg);
    void taskDescription();
    void taskEdited();

    void switchWindow(const QString &windowPath);
    void switchMenu(const QString &panelPath);

    void request(const QString &);
    void handled(const QByteArray &);

    void profileNameChanged();


public slots:
    void bytesWritten(qint64 bytes);
    void readyRead();
    void send(const QString &);

private:
    QTcpSocket m_socket;

    GoogleAuth *m_googleInstance{nullptr};

    Profile m_profile;
    QString m_accessesToken;
    qint64 m_id;

    WorkflowsModel *m_workflows{nullptr};
    KanbanModel *m_kanban{nullptr};
    TaskDescriptionModel *m_task{nullptr};

    AuthorisationResponseHandler *m_authHandler{nullptr};
    ProfileDataResponseHandler *m_profileHandler{nullptr};
    CreateWorkflowResponseHandler *m_createWorkflowHandler{nullptr};
    ArchiveWorkflowResponseHandler *m_archiveWorkflowHandler{nullptr};
    InviteContactResponseHandler *m_inviteContactResponseHandler{nullptr};
    GetWorkflowsResponseHandler *m_getWorkflowsResponseHandler{nullptr};
    EditWorkflowResponseHandler *m_editWorkflowResponseHandler{nullptr};
    GetWorkflowColaborantsResponseHandler *m_getWorkflowColaborantsResponseHandler{nullptr};
    GetWorkflowPanelsResponseHandler *m_getWorkflowPanelsResponseHandler{nullptr};
    GetPanelTasksResponseHandler *m_getPanelTasksResponseHandler{nullptr};
    GetTaskWorkersResponseHandler *m_getTaskWorkersResponseHandler{nullptr};
    GetTaskResponseHandler *m_getTaskResponseHandler{nullptr};
    GetPanelResponseHandler *m_getPanelResponseHandler{nullptr};
    RenamePanelTitleResponseHandler *m_renamePanelTitleResponseHandler{nullptr};
    GetTaskTitleUpdatingResponseHandler *m_getTaskTitleUpdatingResponseHandler{nullptr};
    GetTaskDescriptionResponseHandler *m_getTaskDescriptionResponseHandler{nullptr};
    GetTaskUpdatingResponseHandler *m_getTaskUpdatingResponseHandler{nullptr};
    MoveTaskResponseHandler *m_moveTaskResponseHandler{nullptr};
    RemoveTaskResponseHandler *m_removeTaskResponseHandler{nullptr};
    GetWorkStatusResponseHandler *m_getWorkStatusResponseHandler{nullptr};
    GetTaskWorkerResponseHandler *m_getTaskWorkerResponseHandler{nullptr};
    RemoveTaskWorkerResponseHandler *m_removeTaskWorkerResponseHandler{nullptr};
    GetTaskDoneStatusResponseHandler *m_getTaskDoneStatusResponseHandler{nullptr};

};

#define m_client Client::singleton()
#define m_engine Client::engineSingleton()

#endif //UTRACKER_CLIENT_H
