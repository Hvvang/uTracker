//
// Created by Artem Shemidko on 18.03.2021.
//

#include "CreateDailyTaskResponseHandler.h"

#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

CreateDailyTaskResponseHandler::CreateDailyTaskResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getDailyPlanTask,
            this,  &CreateDailyTaskResponseHandler::processResponse);
}

void CreateDailyTaskResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        dailyTask t;
        t.id = rootObject["taskId"].toInt();
        t.title = rootObject["title"].toString();
        t.status = rootObject["status"].toBool();

        m_client->addDailyTask(t);
    }
}