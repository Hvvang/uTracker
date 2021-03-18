//
// Created by Artem Shemidko on 19.03.2021.
//

#include "ResetDailyPlanResponseHandler.h"

#include <QJsonDocument>
#include <QJsonObject>
#include "Client.h"

ResetDailyPlanResponseHandler::ResetDailyPlanResponseHandler(QObject *parent)
        : AbstractResponseHandler(parent) {
    connect(this, &AbstractResponseHandler::resetDailyPlan,
            this,  &ResetDailyPlanResponseHandler::processResponse);
}

void ResetDailyPlanResponseHandler::processResponse(const QByteArray &data) {
    if (error(data) == AbstractResponseHandler::ResponseErrorType::NotValid) {
        qWarning() << "An error occurred: " << handleMessage(data);
        emit m_client->notification(handleMessage(data));
    }
    else {
        emit m_client->notification(handleMessage(data));
        m_client->resetDailyPlan();
    }
}