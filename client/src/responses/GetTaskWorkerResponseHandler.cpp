//
// Created by Artem Shemidko on 17.03.2021.
//

#include "GetTaskWorkerResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

GetTaskWorkerResponseHandler::GetTaskWorkerResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getTaskWorker,
            this,  &GetTaskWorkerResponseHandler::processResponse);
}

void GetTaskWorkerResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &panelId = rootObject["listId"].toInt();
        const auto &taskId = rootObject["taskId"].toInt();

        Colaborant c;
        c.id = rootObject["userId"].toInt();
        c.name = rootObject["name"].toString();
        c.surname = rootObject["surname"].toString();
        c.icon = c.name.front();
        m_client->addWorker(panelId, taskId, c);
    }
}