//
// Created by Artem Shemidko on 15.03.2021.
//

#include "GetTaskUpdatingResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetTaskUpdatingResponseHandler::GetTaskUpdatingResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::updateTask,
            this,  &GetTaskUpdatingResponseHandler::processResponse);
}

QStringList GetTaskUpdatingResponseHandler::tagsFromJsonArray(const QJsonArray &jsonValue) {
    QStringList tags;
    foreach(const auto& item, jsonValue) {
        tags.push_back(item.toString());
    }
    return tags;
}

void GetTaskUpdatingResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const int &panelId = rootObject.value("listId").toInt();
        const int &taskId = rootObject.value("taskId").toInt();
        const QString &title = rootObject.value("title").toString();
        const QStringList &tags = tagsFromJsonArray(
                QJsonDocument::fromJson(rootObject["tags"].toString().toUtf8()).array());

        m_client->updateTaskPreview(taskId, panelId, title, tags);
        emit m_client->taskEdited();
        emit m_client->notification(handleMessage(data));
    }
}