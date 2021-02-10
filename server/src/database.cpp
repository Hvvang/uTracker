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
    query.exec("create table IF NOT EXISTS UsersCredential (id integer primary key AUTOINCREMENT, email varchar UNIQUE, password varchar, auth_token varchar UNIQUE, first_name varchar, last_name varchar, photo blob, google_token varchar, github_token varchar)");
    query.exec("create table IF NOT EXISTS WorkFlows (id integer primary key AUTOINCREMENT, owner_id int, title varchar, description varchar)");
    query.exec("create table IF NOT EXISTS KanbanPanels (id integer primary key AUTOINCREMENT, workflow_id integer, title varchar)");
    query.exec("create table IF NOT EXISTS Tasks (id integer primary key AUTOINCREMENT, panel_id int, title varchar, creation_time datetime, deadline_time datetime, creator_id int, description varchar, checklist json, files blob)");
    query.exec("create table IF NOT EXISTS T_connector (id integer primary key AUTOINCREMENT, task_id int, worker_id int)");
    query.exec("create table IF NOT EXISTS WF_connector (id integer primary key AUTOINCREMENT, workflow_id int, user_id int)");
}

void DataBase::sendData(Connection *m_connection, int type, const QVariantMap &map) {
    QVariantMap result;
    switch(static_cast<RequestType>(type)) {
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
                           map.value("desctiption").toString());
            break;
        case RequestType::UPDATE_WORKFLOW:
            result = updateWorkflow(map.value("workflowId").toInt(),
                               map.value("title").toString(),
                               map.value("desctiption").toString());
            break;
        case RequestType::INVITE_TO_WORKFLOW:
            result = inviteToWorkflow(map.value("userId").toInt(),
                             map.value("workflowId").toInt());
            break;
        case RequestType::GET_ALL_WORKFLOWS:
            result = getWorkflows(map.value("userId").toInt());
            break;
        case RequestType::GET_SINGLE_WORKFLOW_DATA:
            result = getWorkflow(map.value("workflow_id").toInt());
            break;
        case RequestType::GET_STATISTICS:
            break;
        case RequestType::GET_PROFILE:
            getProfile(map.value("userId").toInt());
            break;
        case RequestType::UPDATE_PROFILE:
            updateProfile(map.value("userId").toInt(),
                          map.value("name").toString(),
                          map.value("surname").toString());
            break;
    }

    if (!result.isEmpty()) {
        QJsonObject jsonObject =  QJsonObject::fromVariantMap(result);
        QJsonDocument jsonDoc = QJsonDocument(jsonObject);
        emit m_connection->sendResponse(jsonDoc.toJson());
    }
}

QVariantMap DataBase::containsUser(const QString &user, const QString &password) {
//    const std::lock_guard<std::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec("select password from UsersCredential where email = \"" + user + "\" or auth_token = \"" + user + "\";");
    query.first();
//    qDebug() << query.value(0).toString();
//    qDebug() << password;
    // query.value(0).toString() == password;
    QMap<QString, QVariant> map;
    map["type"] = static_cast<int>(RequestType::SIGN_IN);
    if (!(query.value(0).toString() == password)) {
        map["error"] = 1;
        map["message"] = "User exist";
    } else {
        map["message"] = "All good";
    }
    return QVariantMap();
}

QVariantMap
DataBase::createUser(const QString &login, const QString &password, const QString &name, const QString &surname) {
    QSqlQuery query;
    query.prepare(
            "INSERT INTO UsersCredential (auth_token, email, password, first_name, last_name) "
            "VALUES (:auth_token, :email, :password, :first_name, :last_name);");
//    query.bindValue(":auth_token", login);
    query.bindValue(":email", login);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_UP);
    if (!query.exec()) {
        map["error"] = 1;
        map["message"] = "Error occurred";
    } else {
        map["message"] = "User successfully created";
    }
    return map;
}

QVariantMap
DataBase::createWorkflow(int owner_id, const QString &title, const QString &description) {
    // set_two_string("WorkFlows", "title", title, "description", description);
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.prepare(
            "INSERT INTO WorkFlows (owner_id, title, description) "
            "VALUES (:owner_id, :title, :description)");
    query.bindValue(":owner_id", owner_id);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.exec();
    return QVariantMap();
}

QVariantMap
DataBase::updateWorkflow(int workflow_id, const QString &title, const QString &description) {
    update_two_string("WorkFlows",
                      "title",
                      title,
                      "description",
                      description,
                      "id",
                      QString(workflow_id));
    return QVariantMap();
}

QVariantMap
DataBase::inviteToWorkflow(int user_id, int workflow_id) {
    set_two_int("WF_connector", "workflow_id", workflow_id, "user_id", user_id);
    return QVariantMap();
}

QVariantMap DataBase::getWorkflows(int user_id) {
    QJsonArray npcArray;
    QSqlQuery query;
    query.prepare("select workflow_id from WF_connector where user_id = :user_id;");
    query.bindValue(":user_id", user_id);
    query.exec();
    QMap<QString, QVariant> maxi_mapa;
    if (query.first()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        npcArray.append(jsonObject);
    }
    else {
        maxi_mapa["error"] = 1;
    }
    while (query.next()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        npcArray.append(jsonObject);
    }
    maxi_mapa["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    maxi_mapa["array"] = npcArray;

    return maxi_mapa;
}

QVariantMap DataBase::getWorkflow(int workflow_id) {
    QSqlQuery query;
    query.prepare("select * from WorkFlows where id = :workflow_id;");
    query.bindValue(":workflow_id", workflow_id);
    query.exec();
    query.first();
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
    mapa["userId"] = query.value(0).toInt();
    mapa["title"] = query.value(1).toString();
    mapa["description"] = query.value(2).toString();
    mapa["message"] = "Nazar";
    return mapa;
}

QVariantMap DataBase::getProfile(int user_id) {
    QSqlQuery query;
    query.exec("select first_name, last_name from WorkFlows where id = " + QString(user_id) + ";");
    query.first();
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_PROFILE);
    mapa["userId"] = query.value(0).toInt();
    mapa["title"] = query.value(1).toString();
    mapa["description"] = query.value(2).toString();
    mapa["message"] = "Nazar";
    //    QString email
    //    QString password
    //    QString auth_token
    //    QString first_name
    //    QString last_name
    //    byte photo
    //    QString google_token
    //    QString github_token varchar
    return mapa;
}

QVariantMap DataBase::updateProfile(int user_id, const QString &name, const QString &surname) {
    update_two_string("UsersCredential", "first_name", name, "last_name", surname, "id", QString(user_id));
    return QVariantMap();
}

void DataBase::update_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2, const QString &column, const QString &string) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec("UPDATE " + table + " SET " + namestr1 + " = \"" + str1 + ", " + namestr2 + " = \"" + str2 + "\" WHERE " + column + " = \"" + string + "\";");
}

void DataBase::set_two_int(const QString &table, const QString &namestr1, int str1, const QString &namestr2, int str2) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.prepare(
        "INSERT INTO " + table + " (" + namestr1 + ", " + namestr2 +
        ") "
        "VALUES (:" +
        namestr1 + ", :" + namestr2 + ")");
    query.bindValue(":" + namestr1, str1);
    query.bindValue(":" + namestr2, str2);
    query.exec();
}


// //QJsonArray npcArray;
// //QVector<int> vitya = {1, 2, 3, 4, 5};
// //for (auto item : vitya) {
// //QJsonObject npcObject {
// //        {"num", item}
// //};
// //npcArray.append(npcObject);
// //}