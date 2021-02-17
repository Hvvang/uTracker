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
#include "WorkflowsModel.h"
#include "KanbanModel.h"


#include "AuthorisationResponseHandler.h"
#include "ProfileDataResponseHandler.h"
#include "CreateWorkflowResponseHandler.h"
#include "ArchiveWorkflowResponseHandler.h"
#include "InviteContactResponseHandler.h"
#include "GetWorkflowsResponseHandler.h"
#include "EditWorkflowResponseHandler.h"
#include "GetWorkflowColaborantsResponseHandler.h"

#define AUTH_CONFIGURE_FILE QCoreApplication::applicationDirPath() + "/.auth_config"

#define UI_AuthWindow "qrc:/qml/authwindow/Authorization.qml"
#define UI_MainWindow "qrc:/qml/mainwindow/Mainwindowview.qml"

struct Profile {
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
        GET_WORKFLOWS = 9,

        GET_STATISTICS = 11,
        GET_PROFILE = 12,
        UPDATE_PROFILE = 13,
        CREATE_LIST = 14,
        REMOVE_LIST = 15,
        CREATE_TASK = 16,
        UPDATE_TASK = 17,
        MOVE_TASK = 18,
        REMOVE_TASK = 19,
        GET_TASK_DATA = 20,
        GET_WORKFLOW_COLABORANT = 21,
    };

    Client(QQmlApplicationEngine *engine = nullptr, const QHostAddress &host = QHostAddress::LocalHost, const quint16 port = 5000, QObject *parent = nullptr);

    void initResponseHandlers();
    void deinitResponseHandlers();
    void saveToken(const QString &type, const QString &value);
    QString getToken(const QString &type);
    static Client* singleton();

    void initWorkflowsModel();
    void getProfileData();
    void getWorkflows();
    void setProfile(const QString &login, const QString &name, const QString &surname);
    void setId(quint64 m_id);

    void autoSignIn();

    QChar nameFirstLetter();
    void newWorkflow(const Workflow &flow);

    void removeWorkflow(int index);
    void addColaborant(quint64 flowIndex, const Colaborant &contact);
    void updateWorkflow(const Workflow &flow);
    void getWorkflowColaborants(int workflowId);
    void reject();

    Q_INVOKABLE void googleAuthorize();
    Q_INVOKABLE void authorize(const QString &email, const QString &password);
    Q_INVOKABLE void registrate(const QString &email, const QString &password, const QString &name, const QString &surname);
    Q_INVOKABLE void openWorkflow(int index);
    Q_INVOKABLE void createWorkflow(const QString &title, const QString &date);
    Q_INVOKABLE void archiveWorkflow(int index);
    Q_INVOKABLE void inviteContact(const QString &contact, int index);
    Q_INVOKABLE void editWorkflow(int index, const QString &title, const QString &date);
    Q_INVOKABLE void logout();

protected:
    static Client* m_instance;

signals:
    void notification(const QString &msg);

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
    QQmlApplicationEngine *m_engine{nullptr};
    GoogleAuth *m_googleInstance{nullptr};

    Profile m_profile;
    QString m_accessesToken;
    qint64 m_id;

    WorkflowsModel *m_workflows{nullptr};
    KanbanModel *m_kanban{nullptr};

    AuthorisationResponseHandler *m_authHandler;
    ProfileDataResponseHandler *m_profileHandler;
    CreateWorkflowResponseHandler *m_createWorkflowHandler;
    ArchiveWorkflowResponseHandler *m_archiveWorkflowHandler;
    InviteContactResponseHandler *m_inviteContactResponseHandler;
    GetWorkflowsResponseHandler *m_getWorkflowsResponseHandler;
    EditWorkflowResponseHandler *m_editWorkflowResponseHandler;
    GetWorkflowColaborantsResponseHandler *m_getWorkflowColaborantsResponseHandler;

};

#define m_client Client::singleton()

#endif //UTRACKER_CLIENT_H
