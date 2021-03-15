//
// Created by Artem Shemidko on 14.03.2021.
//

#include "GetTaskDescriptionResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

GetTaskDescriptionResponseHandler::GetTaskDescriptionResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getTaskDescription,
            this,  &GetTaskDescriptionResponseHandler::processResponse);
}

void GetTaskDescriptionResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
//        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const int &panelId = rootObject.value("listId").toInt();
        const int &taskIndex = rootObject.value("taskIndex").toInt();
        const int &taskId = rootObject.value("taskId").toInt();
        const int &creatorId = rootObject.value("creator_id").toInt();

        const QString &title = rootObject.value("title").toString();
        const QString &creation_time = rootObject.value("creation_time").toString();
        const QString &deadline_time = rootObject.value("deadline_time").toString();
        const QString &description = rootObject.value("description").toString();

        m_client->populateTaskModel(taskId, title, creation_time, deadline_time, description);
        emit m_client->taskDescription();
    }
}