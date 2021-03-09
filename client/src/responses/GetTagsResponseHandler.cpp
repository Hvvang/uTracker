//
// Created by Artem Shemidko on 17.02.2021.
//

#include "GetTagsResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetTagsResponseHandler::GetTagsResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getTaskTags, this,  &GetTagsResponseHandler::processResponse);
}

void GetTagsResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " << static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    } else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        const auto &panelId = rootObject["panelId"].toInt();
        const auto &taskId = rootObject["taskId"].toInt();
        const auto &tasks = rootObject["tasks"].toArray();

        foreach(const QJsonValue &task, tasks) {
            QJsonObject obj = task.toObject();

//            Tag t;
//            t.title = obj["title"].toString();
//            t.fontColor = obj["fontColor"].toString();
//            t.backgroundColor = obj["backgroundColor"].toString();
//            m_client->addTaskTag(panelId, taskId, t);
        }
    }
}