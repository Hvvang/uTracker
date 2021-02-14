#include "ArchiveWorkflowResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

ArchiveWorkflowResponseHandler::ArchiveWorkflowResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::archiveWorkflow, this,  &ArchiveWorkflowResponseHandler::processResponse);
}

void ArchiveWorkflowResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " <<  static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto index = rootObject.value("workflowId").toInt();
        m_client->removeWorkflow(index);
        emit m_client->notification(handleMessage(data));
    }
}
