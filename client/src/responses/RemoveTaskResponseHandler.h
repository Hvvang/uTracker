//
// Created by Artem Shemidko on 16.03.2021.
//

#ifndef CLIENT_REMOVETASKRESPONSEHANDLER_H
#define CLIENT_REMOVETASKRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class RemoveTaskResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit RemoveTaskResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_REMOVETASKRESPONSEHANDLER_H
