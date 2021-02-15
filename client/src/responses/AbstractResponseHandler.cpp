//
// Created by Artem Shemidko on 02.02.2021.
//

#include "AbstractResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>

#include "Client.h"

AbstractResponseHandler::AbstractResponseHandler(QObject *parent)
    : QObject(parent) {
    connect(m_client, &Client::handled, this,  &AbstractResponseHandler::mediator);
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

ResponseType AbstractResponseHandler::type(const QByteArray &data) {
    QJsonDocument itemDoc = QJsonDocument::fromJson(data);
    QJsonObject rootObject = itemDoc.object();

    if (rootObject.contains("type"))
        return static_cast<ResponseType>(rootObject.value("type").toInt());
    else return ResponseType::ERROR;
}

void AbstractResponseHandler::mediator(const QByteArray &data) {
    switch (type(data)) {
        case ResponseType::AUTO_OAUTH:
            emit auth(data); break;
        case ResponseType::AUTO_AUTH:
            emit auth(data); break;
        case ResponseType::SIGN_UP:
            emit auth(data); break;
        case ResponseType::SIGN_IN:
            emit auth(data); break;
        case ResponseType::LOG_OUT:
            emit auth(data); break;
        case ResponseType::PROFILE:
            emit profile(data); break;
        case ResponseType::CREATE_WORKFLOW:
            emit newWorkflow(data); break;
        case ResponseType::ARICHIVE_WORKFLOW:
            emit archiveWorkflow(data); break;
        case ResponseType::INVITE_CONTACT:
            emit inviteContact(data); break;
        case ResponseType::GET_WORKFLOWS:
            emit getWorkflows(data); break;
        case ResponseType::UPDATE_WORKFLOW:
            emit updateWorkflow(data); break;
        case ResponseType::GET_WORKFLOW_COLABORANTS:
            emit getWorkflowColaborants(data); break;


        default:
            qDebug() << "Emit some error in response!";
    }
}