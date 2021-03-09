//
// Created by Artem Shemidko on 02.03.2021.
//

#ifndef CLIENT_GETTASKRESPONSEHANDLER_H
#define CLIENT_GETTASKRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetTaskResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTaskResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};


#endif //CLIENT_GETTASKRESPONSEHANDLER_H
