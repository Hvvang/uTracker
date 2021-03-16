//
// Created by Artem Shemidko on 15.03.2021.
//

#ifndef CLIENT_GETTASKUPDATINGRESPONSEHANDLER_H
#define CLIENT_GETTASKUPDATINGRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetTaskUpdatingResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTaskUpdatingResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
private:
    QStringList tagsFromJsonArray(const QJsonArray &jsonValue);
};

#endif //CLIENT_GETTASKUPDATINGRESPONSEHANDLER_H
