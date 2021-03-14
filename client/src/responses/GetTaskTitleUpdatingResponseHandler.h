//
// Created by Artem Shemidko on 14.03.2021.
//

#ifndef CLIENT_GETTASKTITLEUPDATINGRESPONSEHANDLER_H
#define CLIENT_GETTASKTITLEUPDATINGRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetTaskTitleUpdatingResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTaskTitleUpdatingResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};

#endif //CLIENT_GETTASKTITLEUPDATINGRESPONSEHANDLER_H
