//
// Created by Artem Shemidko on 17.02.2021.
//

#include "GetWorkflowPanelsResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetWorkflowPanelsResponseHandler::GetWorkflowPanelsResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getWorkflowPanels, this,  &GetWorkflowPanelsResponseHandler::processResponse);
}

void GetWorkflowPanelsResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " << static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &workflowId = rootObject["workflowId"].toInt();
        const auto &panels = rootObject["panels"].toArray();

        foreach(const QJsonValue &panel, panels) {
            QJsonObject obj = panel.toObject();

            Kanban k;
            k.id = obj["listId"].toInt();
            k.index = obj["listIndex"].toInt();
            k.title = obj["title"].toString();
            m_client->addPanel(workflowId, k);
        }
    }
}