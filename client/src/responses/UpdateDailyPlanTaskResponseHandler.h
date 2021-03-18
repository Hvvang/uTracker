//
// Created by Artem Shemidko on 18.03.2021.
//

#ifndef CLIENT_UPDATEDAILYPLANTASKRESPONSEHANDLER_H
#define CLIENT_UPDATEDAILYPLANTASKRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class UpdateDailyPlanTaskResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit UpdateDailyPlanTaskResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_UPDATEDAILYPLANTASKRESPONSEHANDLER_H
