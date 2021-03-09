//
// Created by Artem Shemidko on 17.02.2021.
//

#ifndef UTRACKER_GETTAGSRESPONSEHANDLER_H
#define UTRACKER_GETTAGSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetTagsResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetTagsResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //UTRACKER_GETTAGSRESPONSEHANDLER_H
