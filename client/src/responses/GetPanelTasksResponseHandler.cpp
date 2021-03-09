//
// Created by Artem Shemidko on 17.02.2021.
//

#include "GetPanelTasksResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetPanelTasksResponseHandler::GetPanelTasksResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getPanelTasks, this,  &GetPanelTasksResponseHandler::processResponse);
}

void GetPanelTasksResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " << static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto panelId = rootObject["panelId"].toInt();
        auto tasks = rootObject["tasks"].toArray();

        foreach(const QJsonValue &task, tasks) {
            QJsonObject obj = task.toObject();

            Task t;
            t.id = obj["taskId"].toInt();
            t.index = obj["index"].toInt();
            t.title = obj["title"].toString();
            m_client->addTask(panelId, t);
        }
    }
}