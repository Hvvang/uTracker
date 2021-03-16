#include "InviteContactResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

InviteContactResponseHandler::InviteContactResponseHandler(QObject *parent)
    : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::inviteContact, this,  &InviteContactResponseHandler::processResponse);
}

void InviteContactResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto workflowIndex = rootObject.value("workflowId").toInt();
        Colaborant c;
        c.id = rootObject.value("contactId").toInt();
        c.name = rootObject.value("first_name").toString();
        c.surname = rootObject.value("last_name").toString();
        c.icon = c.name.front();
        m_client->addColaborant(workflowIndex, c);
    }
}
