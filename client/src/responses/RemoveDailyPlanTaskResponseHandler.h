//
// Created by Artem Shemidko on 18.03.2021.
//

#ifndef CLIENT_REMOVEDAILYPLANTASKRESPONSEHANDLER_H
#define CLIENT_REMOVEDAILYPLANTASKRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class RemoveDailyPlanTaskResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit RemoveDailyPlanTaskResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};


#endif //CLIENT_REMOVEDAILYPLANTASKRESPONSEHANDLER_H
