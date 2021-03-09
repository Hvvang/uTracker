//
// Created by Artem Shemidko on 02.03.2021.
//

#include "GetPanelResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetPanelResponseHandler::GetPanelResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getPanel, this,  &GetPanelResponseHandler::processResponse);
}

void GetPanelResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " << static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &workflowId = rootObject["workflowId"].toInt();

        Kanban k;
        k.id = rootObject["listId"].toInt();
        k.index = rootObject["listIndex"].toInt();
        k.title = rootObject["title"].toString();
        m_client->addPanel(workflowId, k);
    }
}