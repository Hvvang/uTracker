//
// Created by Artem Shemidko on 17.02.2021.
//

#ifndef UTRACKER_GETTASKWORKERSRESPONSEHANDLER_H
#define UTRACKER_GETTASKWORKERSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetTaskWorkersResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTaskWorkersResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //UTRACKER_GETTASKWORKERSRESPONSEHANDLER_H
