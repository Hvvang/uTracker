//
// Created by Artem Shemidko on 14.02.2021.
//

#include "EditWorkflowResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

EditWorkflowResponseHandler::EditWorkflowResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::updateWorkflow, this,  &EditWorkflowResponseHandler::processResponse);
}

void EditWorkflowResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        Workflow w;
        w.id = rootObject["workflow_id"].toInt();
        w.progress = rootObject["progress"].toInt();
        w.deadline = rootObject["deadline"].toString();
        w.title = rootObject["title"].toString();
        m_client->updateWorkflow(w);
    }
}