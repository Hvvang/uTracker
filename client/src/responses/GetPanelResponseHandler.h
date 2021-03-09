//
// Created by Artem Shemidko on 02.03.2021.
//

#ifndef CLIENT_GETPANELRESPONSEHANDLER_H
#define CLIENT_GETPANELRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetPanelResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetPanelResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_GETPANELRESPONSEHANDLER_H
