//
// Created by Artem Shemidko on 16.03.2021.
//

#ifndef CLIENT_GETWORKSTATUSRESPONSEHANDLER_H
#define CLIENT_GETWORKSTATUSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetWorkStatusResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetWorkStatusResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};

#endif //CLIENT_GETWORKSTATUSRESPONSEHANDLER_H
