//
// Created by Artem Shemidko on 14.02.2021.
//

#ifndef UTRACKER_GETWORKFLOWSRESPONSEHANDLER_H
#define UTRACKER_GETWORKFLOWSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetWorkflowsResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetWorkflowsResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};
#endif //UTRACKER_GETWORKFLOWSRESPONSEHANDLER_H
