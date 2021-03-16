//
// Created by Artem Shemidko on 16.03.2021.
//

#include "MoveTaskResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

MoveTaskResponseHandler::MoveTaskResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::moveTask,
            this, &MoveTaskResponseHandler::processResponse);
}

void MoveTaskResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &taskId = rootObject.value("taskId").toInt();
        const auto &toPanel = rootObject.value("toListId").toInt();
        const auto &toIndex = rootObject.value("toTaskIndex").toInt();
        const auto &fromPanel = rootObject.value("fromListId").toInt();
        const auto &fromIndex = rootObject.value("fromTaskIndex").toInt();
        m_client->updateTaskIndex(taskId, fromPanel, fromIndex, toPanel, toIndex);
    }
}