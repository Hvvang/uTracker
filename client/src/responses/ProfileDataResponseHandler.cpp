//
// Created by Artem Shemidko on 12.02.2021.
//

#include "ProfileDataResponseHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

ProfileDataResponseHandler::ProfileDataResponseHandler(QObject *parent)
    : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::profile, this,  &ProfileDataResponseHandler::processResponse);
}

void ProfileDataResponseHandler::processResponse(const QByteArray &data) {
    qDebug() << "error_type equal " <<  static_cast<int>(error(data));
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

        auto login = rootObject.value("login").toString();
        auto name = rootObject.value("first_name").toString();
        auto surname = rootObject.value("last_name").toString();
        m_client->setProfile(login, name, surname);
    }
}
