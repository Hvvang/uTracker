//
// Created by Artem Shemidko on 14.02.2021.
//

#include "GetWorkflowsResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Client.h"

GetWorkflowsResponseHandler::GetWorkflowsResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::getWorkflows, this,  &GetWorkflowsResponseHandler::processResponse);
}

void GetWorkflowsResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " <<  static_cast<int>(error(data));
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto workflows = rootObject["workflows"].toArray();

        foreach(const QJsonValue &flow, workflows) {
            QJsonObject obj = flow.toObject();

            Workflow w;
            w.id = obj.value("workflowId").toInt();
            w.title = obj.value("title").toString();
            w.deadline = obj.value("deadline").toString();
            w.progress = obj.value("progress").toInt();

//            auto colaborants = rootObject["colaborants"].toArray();
//
//            foreach(const QJsonValue &colaborant, colaborants) {
//                QJsonObject obj = colaborant.toObject();
//
//                Colaborant c;
//                c.id = obj["userId"].toInt();
//                c.status = obj["status"].toString();
//                c.name = obj["first_name"].toString();
//                c.surname = obj["last_name"].toString();
//                c.icon = c.name.front();
//                w.colaborants->add(c);
//            }
            m_client->newWorkflow(w);

        }
    }
}