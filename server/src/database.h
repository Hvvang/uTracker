#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <qDebug>

class DataBase {
public:
    explicit DataBase();
    ~DataBase();
    void create_tables();
    int get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    QString get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    bool exist_user(const QString &user, const QString &password);
    void set_usersCredential(const QString &login, const QString &email, const QString &password, const QString &name, const QString &surname);
    void set_usersCredential(const QString &login, const QString &email, const QString &password);
    void set_string(const QString &table, const QString &column, const QString &string);
    void update_string(const QString &table, const QString &column, const QString &string, const QString &columnchanged, const QString &newstring);
private:
    QSqlDatabase m_db;
};