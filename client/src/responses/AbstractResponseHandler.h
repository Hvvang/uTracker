//
// Created by Artem Shemidko on 02.02.2021.
//

#ifndef UTRACKER_ABSTRACTRESPONSEHANDLER_H
#define UTRACKER_ABSTRACTRESPONSEHANDLER_H

#include <QObject>

class AbstractResponseHandler : public QObject {
Q_OBJECT
public:

    enum class ResponseErrorType {
        NoError = 200,
        NotValid = 1,
        BadToken,
    };
    enum class ResponseType {
        SIGN_UP,
        SIGN_IN,
        LOG_OUT,
        ERROR,
    };

    explicit AbstractResponseHandler(QObject *parent = nullptr);

    ResponseType type(const QByteArray &data);
    ResponseErrorType error(const QByteArray &data);
    QString handleMessage(const QByteArray &data);

    virtual void processResponse(const QByteArray &data) = 0;

signals:
    void handled(const QByteArray &);

    void signUp(const QByteArray &);
    void signIn(const QByteArray &);
    void logOut(const QByteArray &);

private slots:
    void mediator(const QByteArray &);

};


#endif //UTRACKER_ABSTRACTRESPONSEHANDLER_H
