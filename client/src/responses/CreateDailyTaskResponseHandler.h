//
// Created by Artem Shemidko on 18.03.2021.
//

#ifndef CLIENT_CREATEDAILYTASKRESPONSEHANDLER_H
#define CLIENT_CREATEDAILYTASKRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class CreateDailyTaskResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit CreateDailyTaskResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_CREATEDAILYTASKRESPONSEHANDLER_H
