//
// Created by Artem Shemidko on 16.03.2021.
//

#ifndef CLIENT_MOVETASKRESPONSEHANDLER_H
#define CLIENT_MOVETASKRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class MoveTaskResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit MoveTaskResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_MOVETASKRESPONSEHANDLER_H
