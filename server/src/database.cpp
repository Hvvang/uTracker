#include "database.h"

#include <QSqlError>

#include "responses.h"
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
    connect(this, &DataBase::signal_get_int_from_bd, this, &DataBase::get_int_from_bd);
    connect(this, &DataBase::signal_get_qstring_from_bd, this, &DataBase::get_qstring_from_bd);
    connect(this, &DataBase::signal_exist_user, this, &DataBase::exist_user);
    // connect(this, &DataBase::signal_set_usersCredential_3, this, &DataBase::set_usersCredential_3);
    connect(this, &DataBase::signal_set_usersCredential_5, this, &DataBase::set_usersCredential_5);
    connect(this, &DataBase::signal_set_string, this, &DataBase::set_string);
    connect(this, &DataBase::signal_update_string, this, &DataBase::update_string);
    connect(this, &DataBase::signal_to_created_workflow, this, &DataBase::to_created_workflow);
    connect(this, &DataBase::signal_to_update_workflow, this, &DataBase::to_update_workflow);
    connect(this, &DataBase::signal_set_two_string, this, &DataBase::set_two_string);
    connect(this, &DataBase::signal_update_two_string, this, &DataBase::update_two_string);
    connect(this, &DataBase::signal_to_invited_to_workflow, this, &DataBase::to_invited_to_workflow);
    connect(this, &DataBase::signal_set_two_int, this, &DataBase::set_two_int);
    connect(this, &DataBase::signal_send_single_workflow_data, this, &DataBase::send_single_workflow_data);
    connect(this, &DataBase::signal_send_profile, this, &DataBase::send_profile);
    connect(this, &DataBase::signal_to_update_profile, this, &DataBase::to_update_profile);
    connect(this, &DataBase::signal_send_all_workflow_data, this, &DataBase::send_all_workflow_data);
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

int DataBase::get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec("select " + column + " from " + table + " where " + namestring + " = " + string + ";");
    query.first();
    return query.value(0).toInt();
}
QString DataBase::get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec("select " + column + " from " + table + " where " + namestring + " = \"" + string + "\";");
    query.first();
    return query.value(0).toString();
}
void DataBase::exist_user(const QString &user, const QString &password) {
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec("select password from UsersCredential where email = \"" + user + "\" or auth_token = \"" + user + "\";");
    query.first();
    qDebug() << query.value(0).toString();
    qDebug() << password;
    // query.value(0).toString() == password;
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::SIGN_IN);
    if (!(query.value(0).toString() == password)) {
        mapa["error"] = 1;
        mapa["message"] = "User exist";
    } else {
        mapa["message"] = "All good";
    }
    signal_get_answer(mapa);
}
void DataBase::set_usersCredential_5(const QString &login, const QString &email, const QString &password, const QString &name, const QString &surname) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.prepare(
        "INSERT INTO UsersCredential (auth_token, email, password, first_name, last_name) "
        "VALUES (:auth_token, :email, :password, :first_name, :last_name);");
    query.bindValue(":auth_token", login);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::SIGN_UP);
    if (!query.exec()) {
        mapa["error"] = 1;
    } else {
        mapa["message"] = "all good";
    }
    signal_get_answer(mapa);
}

void DataBase::set_usersCredential_3(const QString &login, const QString &email, const QString &password) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.prepare(
        "INSERT INTO UsersCredential (auth_token, email, password) "
        "VALUES (:auth_token, :email, :password)");
    query.bindValue(":auth_token", login);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.exec();
}
void DataBase::set_string(const QString &table, const QString &column, const QString &string) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.prepare(
        "INSERT INTO " + table + " (" + column +
        ") "
        "VALUES (:" +
        column + ")");
    query.bindValue(":" + column, string);
    query.exec();
}
void DataBase::update_string(const QString &table, const QString &column, const QString &string, const QString &columnchanged, const QString &newstring) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec(
        "UPDATE " + table + " SET " + columnchanged + " = \"" + newstring + "\" WHERE " + column + " = \"" + string + "\";");
}

void DataBase::to_created_workflow(int owner_id, const QString &title, const QString &description) {
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
}

void DataBase::to_update_workflow(int workflow_id, const QString &title, const QString &description) {
    update_two_string("WorkFlows", "title", title, "description", description, "id", QString(workflow_id));
}

void DataBase::set_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2) {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.prepare(
        "INSERT INTO " + table + " (" + namestr1 + ", " + namestr2 +
        ") "
        "VALUES (:" +
        namestr1 + ", :" + namestr2 + ")");
    query.bindValue(":" + namestr1, str1);
    query.bindValue(":" + namestr2, str2);
    // if (!query.exec()) {
    //     mapa["error"] = 1;
    // } else {
    //     mapa["message"] = "all good";
    // }
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
void DataBase::to_invited_to_workflow(int user_id, int workflow_id) {
    set_two_int("WF_connector", "workflow_id", workflow_id, "user_id", user_id);
}

void DataBase::send_single_workflow_data(int workflow_id) {  //преоброзовать в json
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec("select * from WorkFlows where id = " + QString(workflow_id) + ";");
    query.first();
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
    mapa["userId"] = query.value(0).toInt();
    mapa["title"] = query.value(1).toString();
    mapa["description"] = query.value(2).toString();
    mapa["message"] = "Nazar";
    signal_get_answer(mapa);
}

void DataBase::send_profile(int user_id) {  //преоброзовать в json
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec("select first_name, last_name from WorkFlows where id = " + QString(user_id) + ";");
    query.first();
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_PROFILE);
    mapa["userId"] = query.value(0).toInt();
    mapa["title"] = query.value(1).toString();
    mapa["description"] = query.value(2).toString();
    mapa["message"] = "Nazar";
    signal_get_answer(mapa);
    //    QString email
    //    QString password
    //    QString auth_token
    //    QString first_name
    //    QString last_name
    //    byte photo
    //    QString google_token
    //    QString github_token varchar
}

void DataBase::to_update_profile(int user_id, const QString &name, const QString &surname) {
    update_two_string("UsersCredential", "first_name", name, "last_name", surname, "id", QString(user_id));
}

void DataBase::send_all_workflow_data(int user_id) {
    QJsonArray npcArray;
    QSqlQuery query;
    qDebug() << query.exec("select workflow_id from WF_connector where user_id = " + QString(user_id) + ";");
    QMap<QString, QVariant> maxi_mapa;
    maxi_mapa["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    user_id++;
    // qDebug() << query.value(0).toInt() << query.value(1).toString() << query.value(2).toString() << user_id;
    if (query.first()) {
        QMap<QString, QVariant> mapa;
        mapa["userId"] = query.value(0).toInt();
        mapa["title"] = query.value(1).toString();
        mapa["description"] = query.value(2).toString();
        mapa["message"] = "Nazar";
        QJsonObject jsonObject = QJsonObject::fromVariantMap(mapa);
        npcArray.append(jsonObject);
    }
    while (query.next()) {
        QMap<QString, QVariant> mapa;
        mapa["userId"] = query.value(0).toInt();
        mapa["title"] = query.value(1).toString();
        mapa["description"] = query.value(2).toString();
        mapa["message"] = "Nazar";
        QJsonObject jsonObject = QJsonObject::fromVariantMap(mapa);
        npcArray.append(jsonObject);
    }
    maxi_mapa["array"] = npcArray;
    signal_get_answer(maxi_mapa);
}

// //QJsonArray npcArray;
// //QVector<int> vitya = {1, 2, 3, 4, 5};
// //for (auto item : vitya) {
// //QJsonObject npcObject {
// //        {"num", item}
// //};
// //npcArray.append(npcObject);
// //}