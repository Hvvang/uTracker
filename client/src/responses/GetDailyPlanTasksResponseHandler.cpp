//
// Created by Artem Shemidko on 18.03.2021.
//

#include "GetDailyPlanTasksResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetDailyPlanTasksResponseHandler::GetDailyPlanTasksResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getDailyPlan,
            this,  &GetDailyPlanTasksResponseHandler::processResponse);
}

void GetDailyPlanTasksResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto tasks = rootObject["tasks"].toArray();

        foreach(const QJsonValue &task, tasks) {
            QJsonObject obj = task.toObject();

            dailyTask t;
            t.id = obj["taskId"].toInt();
            t.title = obj["title"].toString();
            t.status = obj["status"].toBool();

            m_client->addDailyTask(t);
        }
    }
}