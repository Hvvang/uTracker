//
// Created by Artem Shemidko on 18.03.2021.
//

#include "RemoveDailyPlanTaskResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

RemoveDailyPlanTaskResponseHandler::RemoveDailyPlanTaskResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::removeDailyPlanTask,
            this, &RemoveDailyPlanTaskResponseHandler::processResponse);
}

void RemoveDailyPlanTaskResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        m_client->deleteDailyTask(rootObject["taskId"].toInt());
    }
}