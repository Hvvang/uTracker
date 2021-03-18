//
// Created by Artem Shemidko on 18.03.2021.
//

#ifndef CLIENT_GETDAILYPLANTASKSRESPONSEHANDLER_H
#define CLIENT_GETDAILYPLANTASKSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetDailyPlanTasksResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetDailyPlanTasksResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_GETDAILYPLANTASKSRESPONSEHANDLER_H
