//
// Created by Artem Shemidko on 16.03.2021.
//

#include "GetWorkStatusResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

GetWorkStatusResponseHandler::GetWorkStatusResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getWorkStatus,
            this,  &GetWorkStatusResponseHandler::processResponse);
}

void GetWorkStatusResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        m_client->setTaskWorkStatus(rootObject.value("listId").toInt(),
                                    rootObject.value("taskId").toInt(),
                                    rootObject.value("status").toBool());
    }
}