//
// Created by Artem Shemidko on 14.02.2021.
//

#ifndef CLIENT_GETWORKFLOWCOLABORANTSRESPONSEHANDLER_H
#define CLIENT_GETWORKFLOWCOLABORANTSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetWorkflowColaborantsResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetWorkflowColaborantsResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};

#endif //CLIENT_GETWORKFLOWCOLABORANTSRESPONSEHANDLER_H
