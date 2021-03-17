#include "database.h"

#include <QSqlError>
#include <QSqlQueryModel>

#include "server.h"
#include "hash.h"

DataBase *DataBase::m_pInstance = nullptr;
DataBase *DataBase::getInstance() {
    if (m_pInstance == nullptr)
        m_pInstance = new DataBase();
    return m_pInstance;
}
DataBase::DataBase() : m_db(QSqlDatabase::addDatabase("QSQLITE")) {
    m_db.setDatabaseName("myDb.db");
    m_db.open();
    create_tables();
    connect(this, &DataBase::getData, this, &DataBase::sendData);
}

DataBase::~DataBase() {
    m_db.close();
}

void DataBase::create_tables() {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec(
        "create table IF NOT EXISTS UsersCredential ("
        "id integer primary key AUTOINCREMENT,"
        "login varchar UNIQUE,"
        "password varchar,"
        "auth_token varchar UNIQUE,"
        "first_name varchar,"
        "last_name varchar,"
        "email varchar,"
        "photo blob,"
        "google_token varchar,"
        "github_token varchar)");
    query.exec(
        "create table IF NOT EXISTS WorkFlows ("
        "id integer primary key AUTOINCREMENT,"
        "owner_id int,"
        "title varchar,"
        "deadline datetime,"
        "FOREIGN KEY(owner_id) REFERENCES UsersCredential(id) ON UPDATE CASCADE ON DELETE CASCADE)");
    // query.exec("create table IF NOT EXISTS KanbanPanels (id integer primary key AUTOINCREMENT, workflow_id integer, title varchar)");
    query.exec(
        "create table IF NOT EXISTS Tasks ("
        "id integer primary key AUTOINCREMENT,"
        "list_id int,"
        "taskIndex int,"
        "title varchar,"
        "creation_time datetime,"
        "deadline_time datetime,"
        "creator_id int,"
        "description varchar,"
        "tags varchar,"
        "files blob,"
        "FOREIGN KEY(list_id) REFERENCES Lists(id) ON UPDATE CASCADE ON DELETE CASCADE,"
        "FOREIGN KEY(creator_id) REFERENCES UsersCredential(id) ON UPDATE CASCADE ON DELETE CASCADE)");
    query.exec(
        "create table IF NOT EXISTS T_connector ("
        "id integer primary key AUTOINCREMENT,"
        "task_id int,"
        "worker_id int,"
        "FOREIGN KEY(task_id) REFERENCES Tasks(id) ON UPDATE CASCADE ON DELETE CASCADE,"
        "FOREIGN KEY(worker_id) REFERENCES UsersCredential(id) ON UPDATE CASCADE ON DELETE CASCADE)");
    query.exec(
        "create table IF NOT EXISTS WF_connector ("
        "id integer primary key AUTOINCREMENT,"
        "workflow_id int,"
        "user_id int,"
        "FOREIGN KEY(workflow_id) REFERENCES WorkFlows(id) ON UPDATE CASCADE ON DELETE CASCADE,"
        "FOREIGN KEY(user_id) REFERENCES UsersCredential(id) ON UPDATE CASCADE ON DELETE CASCADE)");
    query.exec(
        "create table IF NOT EXISTS Lists ("
        "id integer primary key AUTOINCREMENT, "
        "title varchar, "
        "listIndex int, "
        "workflow_id int,"
        "FOREIGN KEY(workflow_id) REFERENCES WorkFlows(id) ON UPDATE CASCADE ON DELETE CASCADE)");
}

bool DataBase::isValidToken(const QString &token, int type) {
    Q_UNUSED(type);
    QSqlQuery query;
    query.exec("select * from UsersCredential where auth_token = '" + token + "';");
    qDebug() << " TOKEN FROM DB :" << query.value(0).toString() << "  TOKEN FROM CLIENT :" << token;
    //    if (type == static_cast<int>(RequestType::SIGN_UP) || (!token.isEmpty() && query.first()))
    return true;
    //    return false;
}

void DataBase::sendData(Connection *m_connection, int type, const QVariantMap &map) {
    QVariantMap result;
    if (isValidToken(map.value("token").toString(),
                     map.value("type").toInt())) {
        switch (static_cast<RequestType>(type)) {
            case RequestType::AUTO_AUTH:
                break;
            case RequestType::SIGN_UP:
                result = createUser(map.value("login").toString(),
                                    map.value("password").toString(),
                                    map.value("name").toString(),
                                    map.value("surname").toString(),
                                    map.value("email").toString());
                if (result.contains("userId")) {
                    m_connection->setUserId(result.value("userId").toInt());
                }
                break;
            case RequestType::SIGN_IN:
                result = containsUser(map.value("email").toString(),
                                      map.value("password").toString());
                if (result.contains("userId")) {
                    m_connection->setUserId(result.value("userId").toInt());
                }
                break;
            case RequestType::AUTO_OAUTH:
                break;
            case RequestType::LOG_OUT:
                break;
            case RequestType::CREATE_WORKFLOW:
                result = createWorkflow(map.value("userId").toInt(),
                                        map.value("title").toString(),
                                        map.value("deadline").toString());
                break;
            case RequestType::ARCHIVE_WORKFLOW:
                result = removeWorkflow(map.value("workflowId").toInt());
                break;
            case RequestType::UPDATE_WORKFLOW:
                result = updateWorkflow(map.value("workflowId").toInt(),
                                        map.value("title").toString(),
                                        map.value("deadline").toString());
                break;
            case RequestType::INVITE_TO_WORKFLOW:
                result = inviteToWorkflow(map.value("email").toString(),
                                          map.value("workflowId").toInt());
                break;
            case RequestType::REMOVE_FROM_WORKFLOW:
                result = removeFromWorkflow(map.value("userId").toInt(), map.value("workflowId").toInt());
                break;
            case RequestType::GET_USERS_FROM_WORKFLOW:
                result = getUsersFromWorkFlow(map.value("workflowId").toInt());
                break;
            case RequestType::GET_ALL_WORKFLOWS:
                result = getWorkflows(map.value("userId").toInt());
                break;
            case RequestType::GET_SINGLE_WORKFLOW_DATA:
                result = getWorkflow(map.value("workflowId").toInt());
                break;
            case RequestType::GET_STATISTICS:
                break;
            case RequestType::GET_PROFILE:
                result = getProfile(map.value("userId").toInt());
                break;
            case RequestType::UPDATE_PROFILE:
                result = updateProfile(map.value("userId").toInt(),
                                       map.value("name").toString(),
                                       map.value("surname").toString());
                break;
            case RequestType::CREATE_LIST:
                result = createList(map.value("title").toString(),
                                    map.value("workflowId").toInt(),
                                    map.value("listIndex").toInt());
                break;
            case RequestType::RENAME_LIST:
                result = renameList(map.value("title").toString(),
                                    map.value("listId").toInt());
                break;
            case RequestType::GET_LISTS:
                result = getLists(map.value("workflowId").toInt());
                break;
            case RequestType::REMOVE_LIST:
                result = removeList(map.value("listId").toInt());
                break;
            case RequestType::CREATE_TASK:
                result = createTask(map.value("title").toString(),
                                    map.value("listId").toInt(),
                                    map.value("taskIndex").toInt());
                break;
            case RequestType::GET_TASKS:
                result = getTasks(map.value("listId").toInt());
                break;
            case RequestType::UPDATE_TASK_TITLE:
                result = renameTaskTitle(map.value("taskId").toInt(),
                                         map.value("title").toString());
                break;
            case RequestType::UPDATE_TASK:
                result = updateTask(map.value("taskId").toInt(),
                                    map.value("title").toString(),
                                    map.value("deadline_time").toString(),
                                    map.value("creation_time").toString(),
                                    map.value("tags").toString(),
                                    map.value("description").toString());
                break;
            case RequestType::MOVE_TASK:
                result = moveTask(map.value("taskId").toInt(),
                                  map.value("listId").toInt(),
                                  map.value("taskIndex").toInt());
                break;
            case RequestType::REMOVE_TASK:
                result = removeTask(map.value("taskId").toInt());
                break;
            case RequestType::GET_TASK_DATA:
                result = getTaskData(map.value("taskId").toInt());
                break;
            case RequestType::GET_TASK_WORKERS:
                result = getTaskWorkers(map.value("taskId").toInt());
                break;
            case RequestType::NoteWorkStatus:
                result = changeTaskWorkStatus(map.value("taskId").toInt(),
                                     map.value("userId").toInt(),
                                     map.value("status").toInt());
                break;
        }
    } else {
        result["type"] = map.value("type").toInt();
        result["error"] = 1;
        result["message"] = "Invalid token";
    }
    if (!result.isEmpty()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(result);
        QJsonDocument jsonDoc = QJsonDocument(jsonObject);

        emit m_connection->sendResponse(jsonDoc.toJson());
    }
}

QVariantMap DataBase::containsUser(const QString &email, const QString &password) {
    QSqlQuery query;
    query.exec("SELECT id, password, auth_token, first_name, last_name FROM UsersCredential where email = '" + email + "';");
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_IN);

    if (query.first() && (query.value(1).toString() == password)) {
        map["userId"] = query.value(0).toInt();
        map["token"] = query.value(2).toString();
        map["name"] = query.value(3).toString();
        map["surname"] = query.value(4).toString();
        map["email"] = email;

        map["message"] = "Successfully authorized";
    } else {
        map["error"] = 1;
        map["message"] = "Invalid email or password";
    }
    return map;
}

QVariantMap
DataBase::createUser(const QString &login,
                     const QString &password,
                     const QString &name,
                     const QString &surname,
                     const QString &email) {
    QSqlQuery query;
    QString hash = mx_hash(password, login);
    query.prepare(
        "INSERT INTO UsersCredential (login, password, first_name, last_name, auth_token, email) "
        "VALUES (:login, :password, :first_name, :last_name, :auth_token, :email);");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);
    query.bindValue(":auth_token", hash);
    query.bindValue(":email", email);

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_UP);
    if (!query.exec()) {
        map["error"] = 1;
        map["message"] = "User with such login already exist";
    } else {
        map["token"] = hash;
        map["email"] = email;
        map["name"] = name;
        map["surname"] = surname;
        map["userId"] = query.lastInsertId().toInt();
        map["message"] = "User successfully created";
    }
    return map;
}

QVariantMap
DataBase::createWorkflow(int userId, const QString &title, const QString &deadline) {
    QSqlQuery query;
    auto res = query.exec(QString("INSERT INTO WorkFlows (owner_id, title, deadline) VALUES(%1, '%2', '%3');")
                              .arg(userId)
                              .arg(title)
                              .arg(deadline));

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);
    if (res) {
        const auto workflowId = query.lastInsertId().toInt();
        map["workflowId"] = workflowId;
        map["title"] = title;
        map["deadline"] = deadline;
//        map["progress"] = progress;
        map["message"] = "Workflow has been created";
        query.exec(QString("INSERT INTO WF_connector (workflow_id, user_id) VALUES(%1, '%2');")
                       .arg(workflowId)
                       .arg(userId));
    } else {
        map["error"] = 1;
        map["message"] = "Unfortunately, workflow hasn't been created";
    }

    return map;
}

QVariantMap
DataBase::updateWorkflow(int workflow_id, const QString &title, const QString &deadline) {
    QVariantMap map;
    QSqlQuery query;

    bool is_ok = false;
    if (!title.isEmpty() && !deadline.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title + "', deadline = '" + deadline + "'", "id = " + QString::number(workflow_id));
        map["workflow_id"] = workflow_id;
        map["title"] = title;
        map["deadline"] = deadline;
    } else if (deadline.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title + "'", "id = " + QString::number(workflow_id));
        map["title"] = title;
    } else if (title.isEmpty()) {
        is_ok = update("WorkFlows", "deadline = '" + deadline + "'", "id = " + QString::number(workflow_id));
        map["deadline"] = deadline;
    }

    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (is_ok)
        map["message"] = "Workflow successfully updated.";
    else {
        map["error"] = 1;
        map["message"] = "Workflow isn't in database.";
    }

    if (query.exec("SELECT user_id FROM WF_connector WHERE workflow_id = " + QString::number(workflow_id)) && query.first()) {
        do {
            QJsonObject jsonObject = QJsonObject::fromVariantMap(map);
            QJsonDocument jsonDoc = QJsonDocument(jsonObject);
            m_server->sendTo(query.value(0).toInt(), jsonDoc.toJson(QJsonDocument::Compact));
        } while(query.next());
    }
    return map;
}

QVariantMap
DataBase::inviteToWorkflow(const QString &email, int workflow_id) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::INVITE_TO_WORKFLOW);
    QSqlQuery query;
    if (query.exec(QString("select id, first_name, last_name from UsersCredential where email = '%1';").arg(email)) && query.first()) {
        const int &invitedUserId = query.value(0).toInt();
        map["workflowId"] = workflow_id;
        map["userId"] = invitedUserId;
        map["name"] = query.value(1).toString();
        map["surname"] = query.value(2).toString();

        insert("WF_connector", "workflow_id, user_id", QString::number(workflow_id) + ", " + QString::number(invitedUserId));
        if (query.exec("SELECT title, deadline FROM WorkFlows WHERE id = " + QString::number(workflow_id)) && query.first()) {
            QVariantMap map;
            map["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);
            map["workflowId"] = workflow_id;
            map["title"] = query.value(0).toString();
            map["deadline"] = query.value(1).toString();
//        map["progress"] = progress;
            map["message"] = "Workflow has been gotten by invitation.";

            QJsonObject jsonObject = QJsonObject::fromVariantMap(map);
            QJsonDocument jsonDoc = QJsonDocument(jsonObject);
            m_server->sendTo(invitedUserId, jsonDoc.toJson(QJsonDocument::Compact));
        }

        map["message"] = "User successfully invited to Workflow";
    } else {
        map["error"] = 1;
        map["message"] = "Invite canceled";
    }
    return map;
}

QVariantMap DataBase::removeFromWorkflow(int user_id, int workflow_id) {
    QMap<QString, QVariant> map;
    QSqlQuery query;
    map["type"] = static_cast<int>(RequestType::REMOVE_FROM_WORKFLOW);
    if (query.exec("DELETE from WF_connector where id = " + QString::number(user_id) + " and " + " workflow_id = " + QString::number(workflow_id))) {
        map["message"] = "User removed";
    } else {
        map["message"] = "User didn't remove from workflow";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::getWorkflows(int user_id) {  // треба норм дописать мапу яку повертаю з ерорами
    QJsonArray workflows;
    QSqlQuery query;
    query.exec(QString("select workflow_id from WF_connector where user_id = %1;").arg(user_id));
    QVariantMap map;

    map["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    if (query.first()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        workflows.append(jsonObject);
    } else {
        map["error"] = 1;
        map["message"] = "Workflows don't exist";
    }
    while (query.next()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        workflows.append(jsonObject);
    }
    if (!map.contains("error")) {
        map["workflows"] = workflows;
        map["message"] = "Workflows successfully have gotten";
    }
    return map;
}

QVariantMap DataBase::getWorkflow(int workflow_id) {
    QSqlQuery query = select("WorkFlows", "owner_id, title, deadline", "id = " + QString::number(workflow_id));
    QVariantMap map;
    if (query.first()) {
        map["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
        map["workflowId"] = workflow_id;
        map["ownerId"] = query.value(0).toInt();
        map["title"] = query.value(1).toString();
        map["deadline"] = query.value(2).toString();

        map["message"] = "Workflow successfully has gotten.";
    } else {
        map["error"] = 1;
        map["message"] = "External error in GET_WORKFLOW";
    }
    return map;
}

QVariantMap DataBase::removeWorkflow(int workflow_id) {
    QMap<QString, QVariant> map;
    QSqlQuery query;
    QStringList transactions;

    map["type"] = static_cast<int>(RequestType::ARCHIVE_WORKFLOW);
    map["workflowId"] = workflow_id;
    map["message"] = "WorkFlow removed";
    if (query.exec("SELECT user_id FROM WF_connector WHERE workflow_id = " + QString::number(workflow_id)) && query.first()) {
        do {
            QJsonObject jsonObject = QJsonObject::fromVariantMap(map);
            QJsonDocument jsonDoc = QJsonDocument(jsonObject);
            m_server->sendTo(query.value(0).toInt(), jsonDoc.toJson(QJsonDocument::Compact));
        } while(query.next());
    }
    transactions << QString("DELETE FROM Tasks WHERE list_id IN "
                            "(SELECT id FROM Lists WHERE workflow_id = %1);").arg(workflow_id);
    transactions << QString("DELETE FROM T_connector WHERE workflow_id = %1;").arg(workflow_id);
    transactions << QString("DELETE FROM Lists WHERE workflow_id = %1;").arg(workflow_id);
    transactions << QString("DELETE FROM WF_connector WHERE workflow_id = %1;").arg(workflow_id);
    transactions << QString("DELETE FROM WorkFlows WHERE id = %1;").arg(workflow_id);
    foreach(const auto &transaction, transactions) {
        query.exec(transaction);
    }
    return map;
}

QVariantMap DataBase::getProfile(int user_id) {
    QSqlQuery query;
    query.exec("SELECT login, first_name, last_name FROM UsersCredential where id = \"" + QString::number(user_id) + "\";");
    //    QSqlQuery query = select("usersCredential", "login, first_name, last_name", "id = " + QString::number(user_id) + ";");
    // query.exec("select first_name, last_name from WorkFlows where id = " + QString::number(user_id) + ";");
    // QMap<QString, QVariant> map;
    // query.first();
    // qDebug() << "login : " << query.value(0).toString();
    QMap<QString, QVariant> map;

    if (query.first()) {
        map["type"] = static_cast<int>(RequestType::GET_PROFILE);
        map["login"] = query.value(0).toString();
        map["name"] = query.value(1).toString();
        map["surname"] = query.value(2).toString();
        map["message"] = "Profile data has successfully gotten";
    } else {
        map["error"] = 1;
        map["message"] = "User doesn't exist in database";
    }
    //    QString email
    //    QString password
    //    QString auth_token
    //    QString first_name
    //    QString last_name
    //    byte photo
    //    QString google_token
    //    QString github_token varchar
    return map;
}

QVariantMap DataBase::updateProfile(int user_id, const QString &name, const QString &surname) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (update("UsersCredential", "first_name = '" + name + "', last_name = '" + surname + "'", "id = " + QString::number(user_id))) {
        map["message"] = "Profile was succesfully updated";
        map["name"] = name;
        map["surname"] = surname;
    } else {
        map["error"] = 1;
        map["message"] = "Profile hasn't beed updated";
    }
    return map;
}

QVariantMap DataBase::createList(const QString &title, const int &workflowId, const int &listIndex) {
    QVariantMap map;
    QSqlQuery query;

    map["type"] = static_cast<int>(RequestType::CREATE_LIST);
    if (query.exec(QString("INSERT INTO Lists (workflow_id, title, listIndex) VALUES(%1, '%2', %3);")
                           .arg(workflowId)
                           .arg(title)
                           .arg(listIndex))) {
        map["message"] = "List created";
        map["listId"] = query.lastInsertId().toInt();
        map["title"] = title;
        map["workflowId"] = workflowId;
        map["listIndex"] = listIndex;
    } else {
        map["message"] = "List wasn't created";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::renameList(const QString &title, int listId) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::RENAME_LIST);
    QSqlQuery query;
    query.prepare("UPDATE Lists SET title = :title WHERE id = " + QString::number(listId) + ";");
    query.bindValue(":title", title);
    if (query.exec()) {
        query.exec(QString("SELECT index, workflowId where listId = %1 ;").arg(listId));
        map["message"] = "List renamed";
        map["listId"] = listId;
        map["title"] = title;
        map["listIndex"] = query.value(0).toInt();
        map["workflowId"] = query.value(1).toInt();
    } else {
        map["message"] = "List wasn't renamed";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::removeList(int listId) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::REMOVE_LIST);
    QSqlQuery query;
    if (query.exec("DELETE from Lists where id = " + QString::number(listId) + ";")) {
        query.exec("DELETE from Tasks where list_id = " + QString::number(listId) + ";");
        map["message"] = "List removed";
        map["listId"] = listId;
    } else {
        map["message"] = "List wasn't removed";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::getLists(int workflowId) {
    QSqlQuery query;
    QJsonArray panels;
    QVariantMap map;

    map["type"] = static_cast<int>(RequestType::GET_LISTS);
    query.exec("select id, title, listIndex from Lists where workflow_id = " + QString::number(workflowId));
    if (query.first()) {
        QVariantMap panel;
        panel["listId"] = query.value(0).toInt();
        panel["title"] = query.value(1).toString();
        panel["index"] = query.value(2).toInt();
        panels.append(QJsonObject::fromVariantMap(panel));
    } else {
        map["error"] = 1;
        map["message"] = "Lists don't exist";
    }
    while (query.next()) {
        QVariantMap panel;
        panel["listId"] = query.value(0).toInt();
        panel["title"] = query.value(1).toString();
        panel["index"] = query.value(2).toInt();
        panels.append(QJsonObject::fromVariantMap(panel));
    }
    if (!map.contains("error")) {
        map["panels"] = panels;
        map["workflowId"] = workflowId;
        map["message"] = "Lists successfully have gotten";
    }
    return map;
}

QVariantMap DataBase::createTask(const QString &title, const int &listId, const int &taskIndex) {
    QSqlQuery query;
    QVariantMap map;

    query.exec(QString("SELECT deadline FROM WorkFlows where id = (SELECT workflow_id FROM Lists where id = %1);").arg(listId));
    map["type"] = static_cast<int>(RequestType::CREATE_TASK);
    if (query.first() && query.exec(QString("INSERT INTO Tasks "
                           "(list_id, taskIndex, title, creation_time, deadline_time, creator_id) "
                           "VALUES(%1, %2, '%3', '%4', '%5', %6);")
                           .arg(listId)
                           .arg(taskIndex)
                           .arg(title)
                           .arg(QDate::currentDate().toString("dd-MM-yyyy"))
                           .arg(query.value(0).toString())
                           .arg(1))) {
        map["taskId"] = query.lastInsertId().toInt();;
        map["listId"] = listId;
        map["title"] = title;
        map["taskIndex"] = taskIndex;
        map["message"] = "Task successfully created";
    } else {
        map["message"] = "Task wasn't created";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::renameTaskTitle(const int &taskId, const QString &title) {
    QSqlQuery query;
    QVariantMap map;

    map["type"] = static_cast<int>(RequestType::UPDATE_TASK_TITLE);
    if (query.exec("SELECT list_id, taskIndex FROM Tasks WHERE id = " + QString::number(taskId)) && query.first()) {
        int listId = query.value(0).toInt();
        int taskIndex = query.value(1).toInt();
        qDebug() << listId << taskIndex << title;
        if (query.exec(QString("UPDATE Tasks SET title = '%1' WHERE id = %2;")
                               .arg(title)
                               .arg(taskId))) {

            map["taskId"] = taskId;
            map["title"] = title;
            map["listId"] = listId;
            map["taskIndex"] = taskIndex;

            map["message"] = "Task title successfully edited.";
        }
    }
    else {
        map["error"] = static_cast<int>(Errors::TASK_RENAME_ERROR);
        map["message"] = "An error occurred in task editing.";
    }
    return map;
}

QVariantMap DataBase::updateTask(int taskId, const QString &title, const QString &deadline,
                                 const QString &creationTime, const QString &tags, const QString &description) {
    QSqlQuery query;
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_TASK);

    if (query.exec(QString("UPDATE Tasks SET "
                           "title = '%1', "
                           "creation_time = '%2', "
                           "deadline_time = '%3', "
                           "description = '%4', "
                           "tags = '%5' "
                           "WHERE id = %6 ;")
                           .arg(title)
                           .arg(creationTime)
                           .arg(deadline)
                           .arg(description)
                           .arg(tags)
                           .arg(taskId))) {
        map["taskId"] = taskId;
        map["title"] = title;
        map["tags"] = tags;
        if (query.exec("SELECT list_id, taskIndex FROM Tasks WHERE id = " + QString::number(taskId)) && query.first()) {
            map["listId"] = query.value(0).toInt();
            map["taskIndex"] = query.value(1).toInt();
        }
        map["message"] = "Task successfully updated.";
    } else {
        map["message"] = "Task wasn't updated.";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::moveTask(const int &taskId, const int &listId, const int &taskIndex) {
    QVariantMap map;
    QSqlQuery query;

    query.exec("select list_id, taskIndex from Tasks where id = " + QString::number(taskId));

    if (query.first()) {
        const int &currList = query.value(0).toInt();
        const int &currIndex = query.value(1).toInt();
        map["fromListId"] = currList;
        map["fromTaskIndex"] = currIndex;

        query.exec("select id from Tasks where list_id = " + QString::number(currList) + " and taskIndex > " + QString::number(currIndex) + " order by taskIndex desc");
        if (query.first()) {
            update("Tasks", "taskIndex = taskIndex - 1", "id = " + QString::number(query.value(0).toInt()));
            while (query.next()) {
                update("Tasks", "taskIndex = taskIndex - 1", "id = " + QString::number(query.value(0).toInt()));
            }
        }

        query.exec("select id from Tasks where list_id = " + QString::number(listId) + " and taskIndex > " + QString::number(taskIndex - 1) + " order by taskIndex desc");
        if (query.first()) {
            update("Tasks", "taskIndex = taskIndex + 1", "id = " + QString::number(query.value(0).toInt()));
            while (query.next()) {
                update("Tasks", "taskIndex = taskIndex + 1", "id = " + QString::number(query.value(0).toInt()));
            }
        }
    }
    map["type"] = static_cast<int>(RequestType::MOVE_TASK);
    if (update("Tasks", "list_id = " + QString::number(listId) + ", taskIndex = " + QString::number(taskIndex), "id = " + QString::number(taskId))) {
        map["taskId"] = taskId;
        map["toListId"] = listId;
        map["toTaskIndex"] = taskIndex;
        map["message"] = "Task successfully moved.";
    } else {
        map["message"] = "Task wasn't moved.";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::removeTask(int taskId) {
    QVariantMap map;
    QSqlQuery query;

    map["type"] = static_cast<int>(RequestType::REMOVE_TASK);
    query.exec("select list_id from Tasks where id = " + QString::number(taskId));

    if (query.first()) {
        map["listId"] = query.value(0).toInt();
    }
    if (query.exec("DELETE from Tasks where id = " + QString::number(taskId))) {
        map["message"] = "Task successfully removed.";
        map["taskId"] = taskId;
    } else {
        map["message"] = "Task wasn't removed.";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::getTaskData(int taskId) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::GET_TASK_DATA);
    QSqlQuery query;
    if (query.exec("SELECT "
                   "list_id, taskIndex, title, tags, creation_time, deadline_time, creator_id, description "
                   "FROM Tasks "
                   "WHERE id = " + QString::number(taskId)) && query.first()) {
        map["listId"] = query.value(0).toInt();
        map["taskIndex"] = query.value(1).toInt();
        map["title"] = query.value(2).toString();
        map["tags"] = query.value(3).toString();
        map["creation_time"] = query.value(4).toString();
        map["deadline_time"] = query.value(5).toString();
        map["creator_id"] = query.value(6).toInt();
        map["description"] = query.value(7).toString();
        map["taskId"] = taskId;
        if (query.exec(QString("SELECT EXISTS (SELECT 1 FROM T_connector WHERE worker_id = %1 and task_id = %2);")
                                .arg(query.value(6).toInt())
                                .arg(taskId)) && query.first())
            map["status"] = query.value(0).toBool();

        map["message"] = "Task successfully gotten.";
    } else {
        map["message"] = "An error occurred in Task data getting.";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::getTasks(int listId) {
    QSqlQuery query;
    QJsonArray tasks;
    QVariantMap map;

    map["type"] = static_cast<int>(RequestType::GET_TASKS);

    query.exec("select id from Tasks where list_id = " + QString::number(listId) + " order by taskIndex asc");

    if (query.first()) {
        tasks.append(QJsonObject::fromVariantMap(getTaskData(query.value(0).toInt())));
    } else {
        map["error"] = 1;
        map["message"] = "Tasks don't exist";
    }
    while (query.next()) {
        tasks.append(QJsonObject::fromVariantMap(getTaskData(query.value(0).toInt())));
    }
    if (!map.contains("error")) {
        map["tasks"] = tasks;
        map["listId"] = listId;
        map["message"] = "Tasks successfully have gotten";
    }
    return map;
}

QVariantMap DataBase::getUsersFromWorkFlow(int workflow_id) {
    QJsonArray Users;
    QSqlQuery query;
    QVariantMap map;

    map["type"] = static_cast<int>(RequestType::GET_USERS_FROM_WORKFLOW);
    if (query.exec("SELECT first_name, last_name, id "
                   "FROM UsersCredential "
                   "WHERE id IN ("
                   "SELECT user_id "
                   "FROM WF_connector "
                   "WHERE workflow_id = " + QString::number(workflow_id) + ");") && query.first()) {
        do {
            map["name"] = query.value(0).toString();
            map["surname"] = query.value(1).toString();
            map["userId"] = query.value(2).toInt();
            Users.append(QJsonObject::fromVariantMap(map));
        } while (query.next());
        map["colaborants"] = Users;
        map["workflowId"] = workflow_id;
        map["message"] = "Users successfully have gotten";
    } else {
        map["error"] = 1;
        map["message"] = "Workflows don't exist";
    }
    return map;
}

QVariantMap DataBase::getTaskWorkers(const int &taskId) {
    QSqlQuery query;
    QJsonArray users;
    QVariantMap map;

    map["type"] = static_cast<int>(RequestType::GET_TASK_WORKERS);

    if(query.exec("SELECT id, first_name, last_name FROM UsersCredential where id in "
             "(SELECT worker_id FROM T_connector WHERE task_id =  " + QString::number(taskId) + ");") && query.first()) {
        do {
            map["userId"] = query.value(0).toInt();
            map["name"] = query.value(1).toString();
            map["surname"] = query.value(2).toString();
            users.append(QJsonObject::fromVariantMap(map));
        } while (query.next());
        map["taskId"] = taskId;
        map["workers"] = users;
        if (query.exec("SELECT list_id FROM Tasks WHERE id = " + QString::number(taskId)) && query.first()) {
            map["listId"] = query.value(0).toInt();
        }
        map["message"] = "Workers successfully have gotten.";
    } else {
        map["error"] = 1;
        map["message"] = "An error occurred while getting task workers.";
    }
    return map;
}

QVariantMap DataBase::changeTaskWorkStatus(const int &taskId, const int &userId, const bool &status) {
    QSqlQuery query;
    QVariantMap map;

    map["type"] = static_cast<int>(RequestType::NoteWorkStatus);
    if (status) {
        if (query.exec(QString("INSERT INTO T_connector (task_id, worker_id) VALUES(%1, %2);")
                          .arg(taskId)
                          .arg(userId))) {
            map["status"] = status;
            map["taskId"] = taskId;
            map["userId"] = userId;
            map["message"] = "Note work status successfully.";
        } else {
            map["error"] = 1;
            map["message"] = "An error occurred while noting work status.";
        }
    } else {
        if (query.exec(QString("DELETE from T_connector where task_id = %1 and worker_id = %2;")
                           .arg(taskId)
                           .arg(userId))) {
            map["status"] = status;
            map["taskId"] = taskId;
            map["userId"] = userId;
            map["message"] = "Unnote work status successfully.";
        } else {
            map["error"] = 1;
            map["message"] = "An error occurred while unnoting work status.";
        }
    }
    if (!map.contains("error")) {
        if (query.exec("SELECT list_id FROM Tasks WHERE id = " + QString::number(taskId)) && query.first()) {
            map["listId"] = query.value(0).toInt();
        }
    }
    return map;
}

bool DataBase::insert(const QString &table, const QString &insert, const QString &values) {
    QSqlQuery query;
    return query.exec("INSERT INTO " + table + " (" + insert + ") VALUES (" + values + ");");
}
bool DataBase::insert(const QString &table, const QString &insert, const QString &values, int &lastInsert) {
    QSqlQuery query;
    bool exec = query.exec("INSERT INTO " + table + " (" + insert + ") VALUES (" + values + ");");
    lastInsert = query.lastInsertId().toInt();
    return exec;
}
bool DataBase::update(const QString &table, const QString &update, const QString &where) {
    QSqlQuery query;
    return query.exec("UPDATE " + table + " SET " + update + " WHERE " + where + ";");
}
QSqlQuery DataBase::select(const QString &table, const QString &select, const QString &where) {
    QSqlQuery query;
    query.exec("SELECT " + select + " FROM " + table + " WHERE " + where + ";");
    return query;
}

// //QJsonArray npcArray;
// //QVector<int> vitya = {1, 2, 3, 4, 5};
// //for (auto item : vitya) {
// //QJsonObject npcObject {
// //        {"num", item}
// //};
// //npcArray.append(npcObject);
// //}

//QJsonArray array = itemObject["checkList"].toArray();
// qDebug() << "CHECK_LIST :\n";
// for(int i = 0; i < checkList.count(); i++) {
// qDebug() << checkList.at(i)["str"].toString();
// qDebug() << checkList.at(i)["isDone"].toBool();
// }
