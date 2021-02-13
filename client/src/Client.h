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
#include "kanbanmodel.h"


#define AUTH_CONFIGURE_FILE QCoreApplication::applicationDirPath() + "/.auth_config"

#define UI_AuthWindow "qrc:/qml/Authorization.qml"
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
        AUTO_OAUTH = 0,
        AUTO_AUTH = 1,
        SIGN_UP = 2,
        SIGN_IN = 3,

        CREATE_WORKFLOW = 5,
        ARCHIVE_WORKFLOW = 6,

        INVITE_CONTACT = 8,

        GET_WORKFLOWS = 9,

        GET_PROFILE = 11,
    };

    Client(QQmlApplicationEngine *engine = nullptr, const QHostAddress &host = QHostAddress::LocalHost, const quint16 port = 5000, QObject *parent = nullptr);

    void initResponseHandlers();
    void deinitResponseHandlers();
    void saveToken(const QString &type, const QString &value);
    QString getToken(const QString &type);
    static Client* singleton();

    void getProfileData();
    void getWorkflows();
    void setProfile(const QString &login, const QString &name, const QString &surname);
    void setId(quint64 m_id);

    void autoSignIn();

    QChar nameFirstLetter();
    void newWorkflow(const QString &title, const QString &deadline);
    void removeWorkflow(int index);
    void addColaborant(quint64 flowIndex, const Colaborant &contact);


    Q_INVOKABLE void googleAuthorize();
    Q_INVOKABLE void authorize(const QString &email, const QString &password);
    Q_INVOKABLE void registrate(const QString &email, const QString &password, const QString &name, const QString &surname);
    Q_INVOKABLE void openWorkflow(int index);
    Q_INVOKABLE void createWorkflow(const QString &title, const QString &date);
    Q_INVOKABLE void archiveWorkflow(int index);
    Q_INVOKABLE void inviteContact(const QString &contact, int index);


protected:
    static Client* m_instance;

signals:
    void notification(const QString &msg);

    void switchWindow(const QString &windowPath);
    void switchMenu(const QString &panelPath);

    void request(const QString &);
    void handled(const QByteArray &);

    void errorResponse(const QByteArray &);

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
    qint64 m_id = 1;

    WorkflowsModel *m_workflows;
    KanbanModel *m_kanban;
};

#define m_client Client::singleton()

#endif //UTRACKER_CLIENT_H
