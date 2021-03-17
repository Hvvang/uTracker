//
// Created by Artem Shemidko on 17.03.2021.
//

#ifndef CLIENT_GETTASKDONESTATUSRESPONSEHANDLER_H
#define CLIENT_GETTASKDONESTATUSRESPONSEHANDLER_H


#include <AbstractResponseHandler.h>

class GetTaskDoneStatusResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTaskDoneStatusResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};


#endif //CLIENT_GETTASKDONESTATUSRESPONSEHANDLER_H
