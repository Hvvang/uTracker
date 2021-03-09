//
// Created by Artem Shemidko on 14.02.2021.
//

#include "GetWorkflowColaborantsResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetWorkflowColaborantsResponseHandler::GetWorkflowColaborantsResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getWorkflowColaborants, this,  &GetWorkflowColaborantsResponseHandler::processResponse);
}

void GetWorkflowColaborantsResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " << static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto workflowId = rootObject["workflowId"].toInt();
        auto colaborants = rootObject["colaborants"].toArray();

        foreach(const QJsonValue &colaborant, colaborants) {
            QJsonObject obj = colaborant.toObject();

            Colaborant c;
            c.id = obj["userId"].toInt();
            c.name = obj["name"].toString();
            c.surname = obj["surname"].toString();
            c.icon = c.name.front();
            m_client->addColaborant(workflowId, c);
        }
    }
}