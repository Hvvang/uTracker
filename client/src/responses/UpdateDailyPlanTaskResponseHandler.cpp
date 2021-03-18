//
// Created by Artem Shemidko on 18.03.2021.
//

#include "UpdateDailyPlanTaskResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

UpdateDailyPlanTaskResponseHandler::UpdateDailyPlanTaskResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::updateDailyPlanTask,
            this,  &UpdateDailyPlanTaskResponseHandler::processResponse);
}

void UpdateDailyPlanTaskResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject obj = itemDoc.object();

        dailyTask t;
        t.id = obj["taskId"].toInt();
        t.title = obj["title"].toString();
        t.status = obj["status"].toBool();

        m_client->updateDailyTask(obj["taskId"].toInt(),
                                  obj["title"].toString(),
                                  obj["status"].toBool());
    }
}