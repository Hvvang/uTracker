//
// Created by Artem Shemidko on 02.02.2021.
//

#include "AbstractResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>

AbstractResponseHandler::AbstractResponseHandler(QObject *parent)
    : QObject(parent) {
    connect(this, &AbstractResponseHandler::handled, this,  &AbstractResponseHandler::mediator);
}

AbstractResponseHandler::ResponseErrorType AbstractResponseHandler::error(const QByteArray &data) {
    QJsonDocument itemDoc = QJsonDocument::fromJson(data);
    QJsonObject rootObject = itemDoc.object();

    if (rootObject.contains("error"))
        return static_cast<ResponseErrorType>(rootObject.value("error").toInt());
    else return ResponseErrorType::NoError;
}

QString AbstractResponseHandler::handleMessage(const QByteArray &data) {
    QJsonDocument itemDoc = QJsonDocument::fromJson(data);
    QJsonObject rootObject = itemDoc.object();

    return rootObject.value("message").toString();
}

AbstractResponseHandler::ResponseType AbstractResponseHandler::type(const QByteArray &data) {
    QJsonDocument itemDoc = QJsonDocument::fromJson(data);
    QJsonObject rootObject = itemDoc.object();

    if (rootObject.contains("type"))
        return static_cast<ResponseType>(rootObject.value("type").toInt());
    else ResponseType::ERROR;
}

void AbstractResponseHandler::mediator(const QByteArray &data) {
    switch (type(data)) {
        case ResponseType::SIGN_UP:
            emit signUp(data); break;
        case ResponseType::SIGN_IN:
            emit signIn(data); break;
        case ResponseType::LOG_OUT:
            emit logOut(data); break;
        default:
            qDebug() << "Emit some error in response!";
    }
}
