#include "database.h"
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
    query.exec("create table IF NOT EXISTS Task (id integer primary key AUTOINCREMENT, panel_id int, title varchar, creation_time datetime, deadline_time datetime, creator_id int, description varchar, checklist json, files blob)");
    query.exec("create table IF NOT EXISTS T_connector (id integer primary key AUTOINCREMENT, task_id int, worker_id int)");
    query.exec("create table IF NOT EXISTS Save (id integer primary key AUTOINCREMENT, workflow_id int, user_id int)");
}
int DataBase::get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string) {
    QSqlQuery query;
    query.exec("select " + column + " from " + table + " where " + namestring + " = " + string + ";");
    query.first();
    return query.value(0).toInt();
}
QString DataBase::get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string) {
    QSqlQuery query;
    query.exec("select " + column + " from " + table + " where " + namestring + " = \"" + string +"\";");
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
