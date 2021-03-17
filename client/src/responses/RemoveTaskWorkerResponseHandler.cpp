//
// Created by Artem Shemidko on 17.03.2021.
//

#include "RemoveTaskWorkerResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

RemoveTaskWorkerResponseHandler::RemoveTaskWorkerResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::removeTaskWorker,
            this,  &RemoveTaskWorkerResponseHandler::processResponse);
}

void RemoveTaskWorkerResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &panelId = rootObject["listId"].toInt();
        const auto &taskId = rootObject["taskId"].toInt();
        const auto &userId = rootObject["userId"].toInt();

        m_client->removeWorker(panelId, taskId, userId);
    }
}