//
// Created by Artem Shemidko on 17.02.2021.
//

#ifndef UTRACKER_GETWORKFLOWPANELSRESPONSEHANDLER_H
#define UTRACKER_GETWORKFLOWPANELSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetWorkflowPanelsResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetWorkflowPanelsResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};

#endif //UTRACKER_GETWORKFLOWPANELSRESPONSEHANDLER_H
