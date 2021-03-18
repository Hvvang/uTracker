//
// Created by Artem Shemidko on 19.03.2021.
//

#ifndef CLIENT_RESETDAILYPLANRESPONSEHANDLER_H
#define CLIENT_RESETDAILYPLANRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class ResetDailyPlanResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit ResetDailyPlanResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_RESETDAILYPLANRESPONSEHANDLER_H
