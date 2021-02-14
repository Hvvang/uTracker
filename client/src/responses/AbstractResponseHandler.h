//
// Created by Artem Shemidko on 02.02.2021.
//

#ifndef UTRACKER_ABSTRACTRESPONSEHANDLER_H
#define UTRACKER_ABSTRACTRESPONSEHANDLER_H

#include <QObject>

enum class ResponseType {
    AUTO_OAUTH = 0,
    AUTO_AUTH = 1,
    SIGN_UP = 2,
    SIGN_IN = 3,
    LOG_OUT = 4,
    CREATE_WORKFLOW = 5,
    ARICHIVE_WORKFLOW = 6,
    INVITE_CONTACT = 7,
    UPDATE_WORKFLOW = 8,
    GET_WORKFLOWS = 9,
    GET_WORKFLOW_COLABORANTS = 10,

    PROFILE = 11,
    ERROR = 250,
};

class AbstractResponseHandler : public QObject {
Q_OBJECT
public:

    enum class ResponseErrorType {
        NoError = 200,
        NotValid = 1,
        BadToken,
    };

    explicit AbstractResponseHandler(QObject *parent = nullptr);

    ResponseType type(const QByteArray &data);
    ResponseErrorType error(const QByteArray &data);
    QString handleMessage(const QByteArray &data);

    virtual void processResponse(const QByteArray &data) = 0;

signals:
    void auth(const QByteArray &);
    void profile(const QByteArray &);
    void newWorkflow(const QByteArray &);
    void archiveWorkflow(const QByteArray &);
    void inviteContact(const QByteArray &);
    void getWorkflows(const QByteArray &);
    void updateWorkflow(const QByteArray &);
    void getWorkflowColaborants(const QByteArray &);

private slots:
    void mediator(const QByteArray &);

};


#endif //UTRACKER_ABSTRACTRESPONSEHANDLER_H
