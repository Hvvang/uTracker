//
// Created by Artem Shemidko on 17.02.2021.
//

#include "GetTaskWorkersResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetTaskWorkersResponseHandler::GetTaskWorkersResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getTaskWorkers, this,  &GetTaskWorkersResponseHandler::processResponse);
}

void GetTaskWorkersResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " << static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &panelId = rootObject["listId"].toInt();
        const auto &taskId = rootObject["taskId"].toInt();
        const auto &colaborants = rootObject["workers"].toArray();

        foreach(const QJsonValue &colaborant, colaborants) {
            QJsonObject obj = colaborant.toObject();

            Colaborant c;
            c.id = obj["userId"].toInt();
            c.name = obj["name"].toString();
            c.surname = obj["surname"].toString();
            c.icon = c.name.front();
            m_client->addWorker(panelId, taskId, c);

        }
    }
}