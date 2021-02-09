//
// Created by Artem Shemidko on 03.02.2021.
//

#include "AuthorisationResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

AuthorisationResponseHandler::AuthorisationResponseHandler(QObject *parent)
    : AbstractResponseHandler(parent) {
    connect(this, &AuthorisationResponseHandler::signIn, this,  &AuthorisationResponseHandler::processResponse);
}

void AuthorisationResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        // TODO: add this message to pop up in UI
        qWarning() << "An error occurred: " << handleMessage(data);
    }
    else if (error(data) == AbstractResponseHandler::ResponseErrorType::BadToken) {
        // TODO: refresh token
    }
    else {
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);
        QJsonObject rootObject = itemDoc.object();

        auto token = rootObject.value("token").toString();

        m_client->saveToken("auth_token", token);
        m_client->switchWindow(Client::Ui::AuthWindow, Client::Ui::MainWindow);

    }
}
