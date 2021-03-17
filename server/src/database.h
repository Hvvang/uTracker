#pragma once

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <mutex>
#include <thread>

#include "connection.h"
#include "responses.h"

class DataBase : public QObject {
    Q_OBJECT
    QSqlDatabase m_db;
    static DataBase *m_pInstance;
    explicit DataBase();
    ~DataBase();
    DataBase(const DataBase &cs) = delete;
    DataBase &operator=(const DataBase &cs) = delete;
    std::mutex g_i_mutex;

private:
    bool insert(const QString &table, const QString &insert, const QString &values, int &lastInsert);
    bool insert(const QString &table, const QString &insert, const QString &values);
    bool update(const QString &table, const QString &update, const QString &where);
    QSqlQuery select(const QString &table, const QString &select, const QString &where);
    QVariantMap createUser(const QString &login, const QString &password, const QString &name, const QString &surname, const QString &email);
    QVariantMap containsUser(const QString &user, const QString &password);
    QVariantMap createWorkflow(const int &userId, const QString &title, const QString &deadline);
    QVariantMap updateWorkflow(const int &userId, int workflow_id, const QString &title, const QString &deadline);
    QVariantMap inviteToWorkflow(const QString &login, int workflow_id);
    QVariantMap removeFromWorkflow(int user_id, int workflowId);

    QVariantMap getWorkflows(int user_id);
    QVariantMap getWorkflow(int workflow_id);
    QVariantMap getUsersFromWorkFlow(int workflow_id);
    QVariantMap getProfile(int user_id);
    QVariantMap updateProfile(int user_id, const QString &name, const QString &surname);
    QVariantMap removeWorkflow(const int &userId, int workflow_id);

    QVariantMap renameList(const int &userId, const QString &title, int listId);
    QVariantMap createList(const int &userId, const QString& title, const int &workflowId, const int &listIndex);
    QVariantMap removeList(const int &userId, int listId);
    QVariantMap getLists(int workflowId);

    QVariantMap createTask(const int &userId, const QString &title, const int &listId, const int &taskIndex);
    QVariantMap renameTaskTitle(const int &userId, const int &taskId, const QString &title);
    QVariantMap updateTask(const int &userId, int taskId, const QString &title, const QString &deadline,
                           const QString &creationTime, const QString &tags, const QString &description);
    QVariantMap moveTask(const int &userId, const int &taskId, const int &listId, const int &taskIndex);
    QVariantMap removeTask(const int &userId, int taskId);
    QVariantMap getTaskData(int taskId);
    QVariantMap getTasks(int listId);
    QVariantMap getTaskWorkers(const int &taskId);
    QVariantMap changeTaskWorkStatus(const int &taskId, const int &userId, const bool &status);

public:
    static DataBase *getInstance();
    void create_tables();
    bool isValidToken(const QString &token, int type) ;


    void sendData(Connection *m_connection, int type, const QMap<QString, QVariant> &map);

signals:
    void getData(Connection *m_connection, int type, const QMap<QString, QVariant> &map);
};
