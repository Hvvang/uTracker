#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

class DataBase {
    QSqlDatabase m_db;
    static DataBase *m_pInstance;
    explicit DataBase();
    ~DataBase();
    DataBase(const DataBase &cs) = delete;
    DataBase &operator=(const DataBase &cs) = delete;

public:
    static DataBase *getInstance();
    void create_tables();
    int get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    QString get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    bool exist_user(const QString &user, const QString &password);
    void set_usersCredential(const QString &login, const QString &email, const QString &password, const QString &name, const QString &surname);
    void set_usersCredential(const QString &login, const QString &email, const QString &password);
    void set_string(const QString &table, const QString &column, const QString &string);
    void update_string(const QString &table, const QString &column, const QString &string, const QString &columnchanged, const QString &newstring);
    void to_created_workflow(const QString &title, const QString &description);
    void to_update_workflow (const QString &workflow_id ,const QString &title, const QString &description);
    void set_two_string(const QString &table, const QString &namestr1, const QString &str1,const QString &namestr2, const QString &str2);
    void update_two_string(const QString &table, const QString &namestr1, const QString &str1,const QString &namestr2, const QString &str2, const QString &column, const QString &string);
    void to_invited_to_workflow(int user_id, int workflow_id);
    void set_two_int(const QString &table, const QString &namestr1, int str1,const QString &namestr2, int str2);
    void send_single_workflow_data(int workflow_id);
    void send_profile(int user_id);
    void to_update_profile(int user_id, const QString &name, const QString &surname);
};
