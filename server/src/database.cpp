#include "database.h"

#include <QSqlError>
#include <QSqlQueryModel>

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
        "photo blob,"
        "google_token varchar,"
        "github_token varchar)");
    query.exec("create table IF NOT EXISTS WorkFlows (id integer primary key AUTOINCREMENT, owner_id int, title varchar, deadline datetime)");
    query.exec("create table IF NOT EXISTS KanbanPanels (id integer primary key AUTOINCREMENT, workflow_id integer, title varchar)");
    query.exec("create table IF NOT EXISTS Tasks (id integer primary key AUTOINCREMENT, panel_id int, title varchar, creation_time datetime, deadline_time datetime, creator_id int, description varchar, checklist json, files blob)");
    query.exec("create table IF NOT EXISTS T_connector ("
               "id integer primary key AUTOINCREMENT,"
               "task_id int,"
               "worker_id int"
               "FOREIGN KEY(task_id) REFERENCES Tasks(id),"
               "FOREIGN KEY(worker_id) REFERENCES UsersCredential(id)\")");
    query.exec("create table IF NOT EXISTS WF_connector ("
               "id integer primary key AUTOINCREMENT,"
               "workflow_id int,"
               "user_id int,"
               "FOREIGN KEY(workflow_id) REFERENCES WorkFlows(id),"
               "FOREIGN KEY(user_id) REFERENCES UsersCredential(id))");
}

void DataBase::sendData(Connection *m_connection, int type, const QVariantMap &map) {
    QVariantMap result;
    qDebug() << "type is: " << type;
    switch (static_cast<RequestType>(type)) {
        case RequestType::AUTO_AUTH:
            break;
        case RequestType::SIGN_UP:
            result = createUser(map.value("email").toString(),
                                map.value("password").toString(),
                                map.value("name").toString(),
                                map.value("surname").toString());
            break;
        case RequestType::SIGN_IN:
            result = containsUser(map.value("email").toString(),
                                  map.value("password").toString());
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
        case RequestType::UPDATE_WORKFLOW:
            result = updateWorkflow(map.value("workflowId").toInt(),
                                    map.value("title").toString(),
                                    map.value("description").toString());
            break;
        case RequestType::INVITE_TO_WORKFLOW:
            result = inviteToWorkflow(map.value("userId").toInt(),
                                      map.value("workflowId").toInt());
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
        case RequestType::ARCHIVE_WORKFLOW:
            break;
    }
    if (!result.isEmpty()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(result);
        QJsonDocument jsonDoc = QJsonDocument(jsonObject);
        emit m_connection->sendResponse(jsonDoc.toJson());
    }
}

QVariantMap DataBase::containsUser(const QString &login, const QString &password) {
    QSqlQuery query;
    query.exec("SELECT id, password FROM UsersCredential where login = \"" + login + "\";");

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_IN);

    if (query.first())
        qDebug() << "userFound";
    if (query.first() && (query.value(1).toString() == password)) {
        map["userId"] = query.value(0);
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
                     const QString &surname) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO UsersCredential (login, password, first_name, last_name) "
        "VALUES (:login, :password, :first_name, :last_name);");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_UP);
    if (!query.exec()) {
        map["error"] = 1;
        map["message"] = "User with such login already exist";
    } else {
        map["userId"] = query.lastInsertId().toInt();
        map["message"] = "User successfully created";
    }
    return map;
}

QVariantMap
DataBase::createWorkflow(int owner_id, const QString &title, const QString &deadline) {
    // set_two_string("WorkFlows", "title", title, "description", description);
//    insert("WorkFlows", "owner_id, title, description", QString::number(owner_id) + ", '" + title + "', '" + description + "'");
//     QSqlQuery query;
//     query.prepare(
//             "INSERT INTO WorkFlows (owner_id, title, description) "
//             "VALUES (:owner_id, :title, :description)");
//     query.bindValue(":owner_id", owner_id);
//     query.bindValue(":title", title);
//     query.bindValue(":description", description);
//     query.exec();
    QSqlQuery query;
    auto res = query.exec(QString( "INSERT INTO WorkFlows (owner_id, title, deadline) VALUES(%1, '%2',  '%3');")
                           .arg(owner_id)
                           .arg(title)
                           .arg(deadline));

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);

    if (res) {
        auto workflowId = query.lastInsertId().toInt();
        map["workflowId"] = workflowId;
        map["title"] = title;
        map["deadline"] = deadline;
        map["message"] = "Workflow has been created";
        query.exec(QString( "INSERT INTO WF_connector (workflow_id, user_id) VALUES(%1, '%2');")
                           .arg(workflowId)
                           .arg(owner_id));
    }
    else {
        map["error"] = 1;
        map["message"] = "Unfortunately, workflow hasn't been created";
    }

    return map;
}

QVariantMap
DataBase::updateWorkflow(int workflow_id, const QString &title, const QString &description) {
    // update_two_string("WorkFlows",
    //                   "title",
    //                   title,
    //                   "description",
    //                   description,
    //                   "id",
    //                   QString(workflow_id));
    bool is_ok = false;
    if (!title.isEmpty() && !description.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title + "', description = '" + description + "'", "id = " + QString::number(workflow_id));
    } else if (description.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title, "id = " + QString::number(workflow_id));
    } else if (title.isEmpty()) {
        is_ok = update("WorkFlows", "description = '" + description + "'", "id = " + QString::number(workflow_id));
    }
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (is_ok)
        map["message"] = "Заебісь зайшло в Update workflow";
    else {
        map["error"] = 1;
        map["message"] = "User isn't in basadate";
    }
    return map;
}

QVariantMap
DataBase::inviteToWorkflow(int user_id, int workflow_id) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (insert("WF_connector", "workflow_id, user_id", QString::number(workflow_id) + ", " + QString::number(user_id))) {
        map["message"] = "Заебісь зайшло в Invite to Workflow";
    }
    else {
        map["error"] = 1;
        map["message"] = "Huyova зайшло в Invite to Profile";
    }
    return map;
}

QVariantMap DataBase::getWorkflows(int user_id) { // треба норм дописать мапу яку повертаю з ерорами
    QJsonArray workflows;
    QSqlQuery query;
    query.exec(QString("select workflow_id from WF_connector where user_id = %1;").arg(user_id));
    QMap<QString, QVariant> map;

    qDebug() << "user_id is " << user_id;
    qDebug() << query.value(0).toInt();
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
    // query.prepare("select * from WorkFlows where id = :workflow_id;");
    // query.bindValue(":workflow_id", workflow_id);
    // query.exec();
    QMap<QString, QVariant> map;
    if (query.first()) {
        map["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
        map["workflowId"] = workflow_id;
        map["owner_id"] = query.value(0).toInt();
        map["title"] = query.value(1).toString();
        map["deadline"] = query.value(2).toString();
        map["message"] = "Workflow successfully has gotten";
    } else {
        map["error"] = 1;
        map["message"] = "External error";
    }
    return map;
}

QVariantMap DataBase::getProfile(int user_id) {
    QSqlQuery query;
    query.exec("SELECT login, first_name, last_name FROM usersCredential where id = \"" + QString::number(user_id) + "\";");
//    QSqlQuery query = select("usersCredential", "login, first_name, last_name", "id = " + QString::number(user_id) + ";");
    // query.exec("select first_name, last_name from WorkFlows where id = " + QString::number(user_id) + ";");
    QMap<QString, QVariant> map;

    qDebug() << "login : " <<  query.value(0).toString();
    if (query.first()) {
        map["type"] = static_cast<int>(RequestType::GET_PROFILE);
        map["login"] = query.value(0).toString();
        map["first_name"] = query.value(1).toString();
        map["last_name"] = query.value(2).toString();
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
    qDebug() << "map is " << map;
    return map;
}

QVariantMap DataBase::updateProfile(int user_id, const QString &name, const QString &surname) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    // update_two_string("UsersCredential", "first_name", name, "last_name", surname, "id", QString(user_id));
    if (update("usersCredential", "first_name = '" + name + "', last_name = '" + surname + "'", "id = " + QString::number(user_id))) {
        map["message"] = "Заебісь зайшло в UpdateProfile";
    }
    else {
        map["error"] = 1;
        map["message"] = "Huyova зайшло в UpdateProfile";
    }
    return map;
}

    bool DataBase::insert(const QString &table, const QString &insert, const QString &values) {
        QSqlQuery query;
        return query.exec("INSERT INTO " + table + " (" + insert + ") VALUES (" + values + ");");
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