//
// Created by Artem Shemidko on 14.03.2021.
//

#ifndef CLIENT_GETTASKDESCRIPTIONRESPONSEHANDLER_H
#define CLIENT_GETTASKDESCRIPTIONRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetTaskDescriptionResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTaskDescriptionResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
private:
    QStringList tagsFromJsonArray(const QJsonArray &jsonValue);
};

#endif //CLIENT_GETTASKDESCRIPTIONRESPONSEHANDLER_H
