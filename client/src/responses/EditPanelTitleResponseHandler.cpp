//
// Created by Artem Shemidko on 25.02.2021.
//

#include "EditPanelTitleResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

EditPanelTitleResponseHandler::EditPanelTitleResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::updateWorkflow, this,  &EditPanelTitleResponseHandler::processResponse);
}

void EditPanelTitleResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " <<  static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        Workflow w;
        const auto &panelId = rootObject["panelId"].toInt();
        const auto &title = rootObject["title"].toString();
//        m_client->updatePanel(panelId, title);
    }
}