//
// Created by Artem Shemidko on 17.03.2021.
//

#include "GetTaskDoneStatusResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

GetTaskDoneStatusResponseHandler::GetTaskDoneStatusResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getTaskDoneStatus,
            this,  &GetTaskDoneStatusResponseHandler::processResponse);
}

void GetTaskDoneStatusResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        m_client->setTaskDoneStatus(rootObject.value("listId").toInt(),
                                    rootObject.value("taskId").toInt(),
                                    rootObject.value("status").toBool());
    }
}