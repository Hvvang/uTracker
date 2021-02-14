#include "database.h"

#include <QSqlError>
#include <QSqlQueryModel>

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
            "photo blob,"
            "google_token varchar,"
            "github_token varchar)");
    query.exec("create table IF NOT EXISTS WorkFlows (id integer primary key AUTOINCREMENT, owner_id int, title varchar, description varchar)");
    query.exec("create table IF NOT EXISTS KanbanPanels (id integer primary key AUTOINCREMENT, workflow_id integer, title varchar)");
    query.exec("create table IF NOT EXISTS Tasks (id integer primary key AUTOINCREMENT, panel_id int, title varchar, creation_time datetime, deadline_time datetime, creator_id int, description varchar, checklist json, files blob)");
    query.exec("create table IF NOT EXISTS T_connector (id integer primary key AUTOINCREMENT, task_id int, worker_id int)");
    query.exec("create table IF NOT EXISTS WF_connector (id integer primary key AUTOINCREMENT,workflow_id int, user_id int, UNIQUE (workflow_id, user_id))");
}

bool DataBase::isValidToken(QJsonObject itemObject) {
//    Q_UNUSED(itemObject);
    if(!itemObject["token"].toString().isEmpty())
        return true;
    return false;
}

void DataBase::sendData(Connection *m_connection, int type, const QVariantMap &map) {
    QVariantMap result;
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
            result = createWorkflow(map.value("ownerId").toInt(),
                    map.value("title").toString(),
                    map.value("description").toString());
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
        case RequestType::CREATE_LIST :
            result = createList(map.value("title").toString(),
                    map.value("workdlowId").toInt());
            break;
        case RequestType::REMOVE_LIST :
            result = removeList(map.value("listId").toInt());
            break;
        case RequestType::CREATE_TASK :
            result = createTask(map.value("title").toString(),
                    map.value("listId").toInt());
            break;
        case RequestType::UPDATE_TASK :
            result = updateTask(map.value("taskId").toInt(),
                    map.value("description").toString(),
                    map.value("checkList").toStringList());
            break;
        case RequestType::MOVE_TASK :
            result = moveTask(map.value("taskId").toInt(),
                    map.value("listId").toInt());
            break;
        case RequestType::REMOVE_TASK :
            result = removeTask(map.value("taskId").toInt());
            break;
        case RequestType::GET_TASK_DATA :
            result = getTaskData(map.value("taskId").toInt());
            break;
    }
    if (!result.isEmpty()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(result);
        QJsonDocument jsonDoc = QJsonDocument(jsonObject);

        qDebug() << jsonDoc.toJson();

        emit m_connection->sendResponse(jsonDoc.toJson());
    }
}


QVariantMap DataBase::containsUser(const QString &login, const QString &password) {
    QSqlQuery query;
    query.exec("SELECT password FROM UsersCredential where login = \"" + login + "\";");

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_IN);

    qDebug() << "Try to authorize" << login << password;

    if (query.first())
        qDebug() << "userFound";
    if (query.first() && (query.value(0).toString() == password)) {
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
            "INSERT INTO UsersCredential (login, password, first_name, last_name, auth_token) "
            "VALUES (:login, :password, :first_name, :last_name, *auth_token);");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);
    query.bindValue(":auth_token", mx_hash(password, login));

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_UP);
    if (!query.exec()) {
        map["error"] = 1;
        map["message"] = "User with such login already exist";
        map["token"] = mx_hash(password, login);
    } else {
        map["message"] = "User successfully created";
    }
    return map;
}

QVariantMap
DataBase::createWorkflow(int owner_id, const QString &title, const QString &description) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);
    if (insert("WorkFlows", "owner_id, title, description", QString::number(owner_id) + ", '" + title + "', '" + description + "'")) {
        map["message"] = "Workflow successfully created";
        //map["workflowId"] = Даша, витягни будь ласка workflowId яку тільки що створили;
    }
    else {
        map["error"] = 1;
        map["message"] = "Workflow hasn't been created";
    }
    return map;
}

QVariantMap
DataBase::updateWorkflow(int workflow_id, const QString &title, const QString &description) {
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
        map["message"] = "Workflow successfully updated";
    else {
        map["error"] = 1;
        map["message"] = "User isn't in database";
    }
    return map;
}

QVariantMap
DataBase::inviteToWorkflow(int user_id, int workflow_id) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (insert("WF_connector", "workflow_id, user_id", QString::number(workflow_id) + ", " + QString::number(user_id))) {
        map["message"] = "User succesfully invited to Workflow";
    }
    else {
        map["error"] = 1;
        map["message"] = "Invite canceled";
    }
    return map;
}

QVariantMap DataBase::getWorkflows(int user_id) { // треба норм дописать мапу яку повертаю з ерорами
    QJsonArray npcArray;
    QSqlQuery query;
    query.prepare("select workflow_id from WF_connector where user_id = :user_id;");
    query.bindValue(":user_id", user_id);
    query.exec();
    QMap<QString, QVariant> maxi_mapa;
    if (query.first()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        npcArray.append(jsonObject);
    } else {
        maxi_mapa["error"] = 1;
    }
    while (query.next()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        npcArray.append(jsonObject);
    }
    maxi_mapa["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    maxi_mapa["array"] = npcArray;
    maxi_mapa["message"] = "Заебісь зайшло в getWorkflows";

    return maxi_mapa;
}

QVariantMap DataBase::getWorkflow(int workflow_id) {
    QSqlQuery query = select("WorkFlows", "*", "id = " + QString::number(workflow_id));
    // query.prepare("select * from WorkFlows where id = :workflow_id;");
    // query.bindValue(":workflow_id", workflow_id);
    // query.exec();
    QMap<QString, QVariant> mapa;
    if (query.first()) {
        mapa["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
        mapa["userId"] = query.value(0).toInt();
        mapa["title"] = query.value(1).toString();
        mapa["description"] = query.value(2).toString();
        mapa["message"] = "Single workflow sent";
    } else {
        mapa["error"] = 1;
        mapa["message"] = "workflowId isn't in database";
    }
    return mapa;
}

QVariantMap DataBase::getProfile(int user_id) {
    QSqlQuery query = select("WorkFlows", "first_name, last_name", "id = " + QString::number(user_id) + ";");
    // query.exec("select first_name, last_name from WorkFlows where id = " + QString::number(user_id) + ";");
    QMap<QString, QVariant> mapa;
    if (query.first()) {
        mapa["type"] = static_cast<int>(RequestType::GET_PROFILE);
        mapa["userId"] = query.value(0).toInt();
        mapa["title"] = query.value(1).toString();
        mapa["description"] = query.value(2).toString();
        mapa["message"] = "Profile sent";
    } else {
        mapa["error"] = 1;
        mapa["message"] = "User isn't in database";
    }
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
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    // update_two_string("UsersCredential", "first_name", name, "last_name", surname, "id", QString(user_id));
    if (update("UsersCredential", "first_name = '" + name + "', last_name = '" + surname + "'", "id = " + QString::number(user_id))) {
        map["message"] = "Profile was succesfully updated";
    }
    else {
        map["error"] = 1;
        map["message"] = "Profile hasn't beed updated";
    }
    return map;
}

QVariantMap DataBase::createList(const QString& title, int workflowId) {
    Q_UNUSED(workflowId);
    Q_UNUSED(title);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_LIST);
    map["message"] = "List created";
    //додать до бд і поставить перевірки типу
    //if(додалось == тру)
    //map["message"] = "List created";
    //else {
    //map["message"] = "List wasn't created";
    //map["error"] = 1;
    return map;
}

QVariantMap DataBase::removeList(int listId) {
    Q_UNUSED(listId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::REMOVE_LIST);
    map["message"] = "List removed";
    //додать до бд і поставить перевірки типу
    //if(видалилось == тру)
    //map["message"] = "List removed";
    //else {
    //map["message"] = "List wasn't removed";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::createTask(const QString& title, int listId) {
    Q_UNUSED(listId);
    Q_UNUSED(title);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_TASK);
    map["message"] = "Task created";
    //додать до бд і поставить перевірки типу
    //if(створилось == тру)
    //map["message"] = "Task created";
    //else {
    //map["message"] = "Task wasn't created";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::updateTask(int taskId, const QString& description, const QStringList& checkList) {
    Q_UNUSED(taskId);Q_UNUSED(description);Q_UNUSED(checkList);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_TASK);
    map["message"] = "Task updated";
    //додать до бд // поки що я ебу як додать чек лист( там має бути типа масив даних в парі (булевське значення і інфа(стрінг))) тому поки що передаю чисто стрінгліст із інфою і буль поки не даю
    //поставить перевірки типу
    //if(оновились дані  == тру)
    //map["message"] = "Task updated";
    //else {
    //map["message"] = "Task wasn't updated";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::moveTask(int taskId, int listId) {
    Q_UNUSED(taskId);
    Q_UNUSED(listId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::MOVE_TASK);
    map["message"] = "Task moved";
    //додать до бд і поставить перевірки типу
    //if(змінила приналежність таски з листа попередньго айді на нове лістІд  == тру)
    //map["message"] = "Task moved";
    //else {
    //map["message"] = "Task wasn't moved";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::removeTask(int taskId) {
    Q_UNUSED(taskId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::REMOVE_TASK);
    map["message"] = "Task removed";
    //додать до бд і поставить перевірки типу
    //if(видалила таску  == тру)
    //map["message"] = "Task removed";
    //else {
    //map["message"] = "Task wasn't removed";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::getTaskData(int taskId) {
    Q_UNUSED(taskId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::GET_TASK_DATA);
    map["message"] = "Take your task data bitch";
    //витягнуть дані з бд і поставить перевірки типу
    //if(видалила таску  == тру) {
    //map["description"] = //витягни з бд, якщо пусто то відправляй пусте;
    //map["checkList"] = //витягни з бд, якщо пусто то відправляй пусте;
    //}
    //else {
    //map["message"] = "i dont now wtf";
    //map["error"] = 1;
    //}
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

//QJsonArray array = itemObject["checkList"].toArray();
//qDebug() << "CHECK_LIST :\n";
//for(int i = 0; i < array.count(); i++)
//qDebug() << array.at(i).toString();
//qDebug() << "\n";