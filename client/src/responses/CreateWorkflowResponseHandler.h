//
// Created by Artem Shemidko on 13.02.2021.
//

#ifndef UTRACKER_CREATEWORKFLOWRESPONSEHANDLER_H
#define UTRACKER_CREATEWORKFLOWRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class CreateWorkflowResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit CreateWorkflowResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //UTRACKER_CREATEWORKFLOWRESPONSEHANDLER_H
