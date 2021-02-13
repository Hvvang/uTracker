//
// Created by Artem Shemidko on 13.02.2021.
//

#include "CreateWorkflowResponseHandler.h"

#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

CreateWorkflowResponseHandler::CreateWorkflowResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::newWorkflow, this,  &CreateWorkflowResponseHandler::processResponse);
}

void CreateWorkflowResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " <<  static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto title = rootObject.value("title").toString();
        auto deadline = rootObject.value("deadline").toString();

        m_client->newWorkflow(title, deadline);
    }
}