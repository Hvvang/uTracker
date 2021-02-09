#pragma once
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <mutex>
#include <thread>

class DataBase : public QObject {
        Q_OBJECT
    QSqlDatabase m_db;
    static DataBase *m_pInstance;
    explicit DataBase();
    ~DataBase();
    DataBase(const DataBase &cs) = delete;
    DataBase &operator=(const DataBase &cs) = delete;
    std::mutex g_i_mutex;

public slots:
    static DataBase *getInstance();
    void create_tables();
    int get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    QString get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    void exist_user(const QString &user, const QString &password);
    void set_usersCredential_5(const QString &login, const QString &email, const QString &password, const QString &name, const QString &surname);
    void set_usersCredential_3(const QString &login, const QString &email, const QString &password);
    void set_string(const QString &table, const QString &column, const QString &string);
    void update_string(const QString &table, const QString &column, const QString &string, const QString &columnchanged, const QString &newstring);
    void to_created_workflow(int owner_id, const QString &title, const QString &description);
    void to_update_workflow(int workflow_id, const QString &title, const QString &description);
    void set_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2);
    void update_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2, const QString &column, const QString &string);
    void to_invited_to_workflow(int user_id, int workflow_id);
    void set_two_int(const QString &table, const QString &namestr1, int str1, const QString &namestr2, int str2);
    void send_single_workflow_data(int workflow_id);
    void send_profile(int user_id);
    void to_update_profile(int user_id, const QString &name, const QString &surname);
    void send_all_workflow_data(int user_id);

signals:
    int signal_get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    QString signal_get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    void signal_exist_user(const QString &user, const QString &password);
    void signal_set_usersCredential_5(const QString &login, const QString &email, const QString &password, const QString &name, const QString &surname);
    void signal_set_usersCredential_3(const QString &login, const QString &email, const QString &password);
    void signal_set_string(const QString &table, const QString &column, const QString &string);
    void signal_update_string(const QString &table, const QString &column, const QString &string, const QString &columnchanged, const QString &newstring);
    void signal_to_created_workflow(int owner_id, const QString &title, const QString &description);
    void signal_to_update_workflow(int workflow_id, const QString &title, const QString &description);
    void signal_set_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2);
    void signal_update_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2, const QString &column, const QString &string);
    void signal_to_invited_to_workflow(int user_id, int workflow_id);
    void signal_set_two_int(const QString &table, const QString &namestr1, int str1, const QString &namestr2, int str2);
    void signal_send_single_workflow_data(int workflow_id);
    void signal_send_profile(int user_id);
    void signal_to_update_profile(int user_id, const QString &name, const QString &surname);
    void signal_send_all_workflow_data(int user_id);
    void signal_get_answer(const QMap<QString, QVariant> &mapa);
};
