//
// Created by Artem Shemidko on 16.03.2021.
//

#include "RemoveTaskResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

RemoveTaskResponseHandler::RemoveTaskResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::removeTask,
            this,  &RemoveTaskResponseHandler::processResponse);
}

void RemoveTaskResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &panelId = rootObject["listId"].toInt();
        const auto &taskId = rootObject["taskId"].toInt();

        m_client->deleteTask(panelId, taskId);
    }
}