//
// Created by Artem Shemidko on 14.03.2021.
//

#include "GetTaskTitleUpdatingResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

GetTaskTitleUpdatingResponseHandler::GetTaskTitleUpdatingResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::renameTask, this,  &GetTaskTitleUpdatingResponseHandler::processResponse);
}

void GetTaskTitleUpdatingResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
//        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        m_client->renameTask(rootObject["taskId"].toInt(),
                             rootObject["listId"].toInt(),
                             rootObject["title"].toString());
    }
}