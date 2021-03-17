//
// Created by Artem Shemidko on 17.03.2021.
//

#ifndef CLIENT_GETTASKWORKERRESPONSEHANDLER_H
#define CLIENT_GETTASKWORKERRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetTaskWorkerResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTaskWorkerResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_GETTASKWORKERRESPONSEHANDLER_H
