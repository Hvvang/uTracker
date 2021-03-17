//
// Created by Artem Shemidko on 12.03.2021.
//

#include "RenamePanelTitleResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

RenamePanelTitleResponseHandler::RenamePanelTitleResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::renamePanel,
            this,  &RenamePanelTitleResponseHandler::processResponse);
}

void RenamePanelTitleResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &workflowId = rootObject["workflowId"].toInt();
        const auto &panelIndex = rootObject["listIndex"].toInt();
        const auto &title = rootObject["title"].toString();

        m_client->renamePanel(workflowId, panelIndex, title);
    }
}