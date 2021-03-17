//
// Created by Artem Shemidko on 17.03.2021.
//

#ifndef CLIENT_REMOVETASKWORKERRESPONSEHANDLER_H
#define CLIENT_REMOVETASKWORKERRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class RemoveTaskWorkerResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit RemoveTaskWorkerResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_REMOVETASKWORKERRESPONSEHANDLER_H
