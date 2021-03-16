//
// Created by Artem Shemidko on 02.03.2021.
//

#include "GetTaskResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetTaskResponseHandler::GetTaskResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getTask, this,  &GetTaskResponseHandler::processResponse);
}

QStringList GetTaskResponseHandler::tagsFromJsonArray(const QJsonArray &jsonValue) {
    QStringList tags;
    foreach(const auto& item, jsonValue) {
        tags.push_back(item.toString());
    }
    return tags;
}

void GetTaskResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " << static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &panelId = rootObject["listId"].toInt();

        Task t;
        t.id = rootObject["taskId"].toInt();
        t.index = rootObject["taskIndex"].toInt();
        t.title = rootObject["title"].toString();
        t.tags = tagsFromJsonArray(
                QJsonDocument::fromJson(rootObject["tags"].toString().toUtf8()).array());
        m_client->addTask(panelId, t);
    }
}