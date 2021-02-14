//
// Created by Artem Shemidko on 03.02.2021.
//

#include "AuthorisationResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

AuthorisationResponseHandler::AuthorisationResponseHandler(QObject *parent)
    : AbstractResponseHandler(parent) {
    connect(this, &AuthorisationResponseHandler::auth, this,  &AuthorisationResponseHandler::processResponse);
}

void AuthorisationResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {

        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else if (error(data) == AbstractResponseHandler::ResponseErrorType::BadToken) {
        // TODO: refresh token
//        m_client->refresh_token();
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        qDebug() << rootObject;
        auto type = static_cast<ResponseType>(rootObject["type"].toInt());
        if (type == ResponseType::LOG_OUT) {
            m_client->reject();
            emit m_client->switchWindow(UI_AuthWindow);
        }
        else {
            auto token = rootObject.value("token").toString();
            auto id = rootObject.value("userId").toInt();

            m_client->saveToken("auth_token", token);
            m_client->setId(id);
            m_client->initWorkflowsModel();
            m_client->notification(handleMessage(data));
            m_client->getProfileData();
            m_client->getWorkflows();
            emit m_client->switchWindow(UI_MainWindow);
        }
    }
}
