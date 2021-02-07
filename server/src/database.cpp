#include "database.h"

DataBase *DataBase::m_pInstance = nullptr;
DataBase *DataBase::getInstance() {
    if (m_pInstance == nullptr)
        m_pInstance = new DataBase();
    return m_pInstance;
}
DataBase::DataBase() : m_db(QSqlDatabase::addDatabase("QSQLITE")) {
    m_db.setDatabaseName("myDb.db");
    m_db.open();
}
DataBase::~DataBase() {
    m_db.close();
}
void DataBase::create_tables() {
    QSqlQuery query;
        query.exec("create table IF NOT EXISTS UsersCredential (id integer primary key AUTOINCREMENT, email varchar, password varchar, auth_token varchar, first_name varchar, last_name varchar, photo blob, google_token varchar, github_token varchar)");
        query.exec("create table IF NOT EXISTS WorkFlows (id integer primary key AUTOINCREMENT, owner_id int, title varchar, description varchar)");
        query.exec("create table IF NOT EXISTS KanbanPanels (id integer primary key AUTOINCREMENT, workflow_id integer, title varchar)");
        query.exec("create table IF NOT EXISTS Tasks (id integer primary key AUTOINCREMENT, panel_id int, title varchar, creation_time datetime, deadline_time datetime, creator_id int, description varchar, checklist json, files blob)");
        query.exec("create table IF NOT EXISTS T_connector (id integer primary key AUTOINCREMENT, task_id int, worker_id int)");
        query.exec("create table IF NOT EXISTS WF_connector (id integer primary key AUTOINCREMENT, workflow_id int, user_id int)");
}

int DataBase::get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string) {
    QSqlQuery query;
    query.exec("select " + column + " from " + table + " where " + namestring + " = " + string + ";");
    query.first();
    return query.value(0).toInt();
}
QString DataBase::get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string) {
    QSqlQuery query;
    query.exec("select " + column + " from " + table + " where " + namestring + " = \"" + string + "\";");
    query.first();
    return query.value(0).toString();
}
bool DataBase::exist_user(const QString &user, const QString &password) {
    QSqlQuery query;
    query.exec("select password from UsersCredential where email = \"" + user + "\" or auth_token = \"" + user + "\";");
    query.first();
    return query.value(0).toString() == password;
}
void DataBase::set_usersCredential(const QString &login, const QString &email, const QString &password, const QString &name, const QString &surname) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO UsersCredential (auth_token, email, password, first_name, last_name) "
        "VALUES (:auth_token, :email, :password, :first_name, :last_name)");
    query.bindValue(":auth_token", login);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);
    query.exec();
}
void DataBase::set_usersCredential(const QString &login, const QString &email, const QString &password) {
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
    QSqlQuery query;
    query.exec(
        "UPDATE " + table + " SET " + columnchanged + " = \"" + newstring + "\" WHERE " + column + " = \"" + string + "\";");
}
void DataBase::to_created_workflow(const QString &title, const QString &description) {
    set_two_string("WorkFlows", "title", title, "description", description);
}

void DataBase::to_update_workflow(const QString &workflow_id ,const QString &title, const QString &description) {
    update_two_string("WorkFlows", "title", title, "description", description, "id", workflow_id);
}

void DataBase::set_two_string(const QString &table, const QString &namestr1, const QString &str1,const QString &namestr2, const QString &str2) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO "+ table +" ("+ namestr1 + ", "+ namestr2 +") "
        "VALUES (:"+ namestr1 +", :" +namestr2 + ")");
    query.bindValue(":" + namestr1, str1);
    query.bindValue(":" + namestr2, str2);
    query.exec();
}

void DataBase::update_two_string(const QString &table, const QString &namestr1, const QString &str1,const QString &namestr2, const QString &str2, const QString &column, const QString &string) {
    QSqlQuery query;
    query.exec("UPDATE " + table + " SET " + namestr1 + " = \"" + str1 + ", "+ namestr2 + " = \"" + str2 +"\" WHERE " + column + " = \"" + string + "\";");
}

void DataBase::set_two_int(const QString &table, const QString &namestr1, int str1,const QString &namestr2, int str2) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO "+ table +" ("+ namestr1 + ", "+ namestr2 +") "
        "VALUES (:"+ namestr1 +", :" +namestr2 + ")");
    query.bindValue(":" + namestr1, str1);
    query.bindValue(":" + namestr2, str2);
    query.exec();
}
void DataBase::to_invited_to_workflow(int user_id, int workflow_id) {
    set_two_int("WF_connector", "workflow_id", workflow_id, "user_id", user_id);
}

void DataBase::send_single_workflow_data(int workflow_id) { //преоброзовать в json
    QSqlQuery query;
    query.exec("select * from WorkFlows where id = " + QString(workflow_id) + ";");
    query.first();
    int owner_id = query.value(0).toInt();
    QString title = query.value(1).toString();
    QString description = query.value(2).toString();
    qDebug() << owner_id << " " << title << " " << description;
}

void DataBase::send_profile(int user_id) { //преоброзовать в json
    QSqlQuery query;
    query.exec("select * from WorkFlows where id = " + QString(user_id) + ";");
    query.first();
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
