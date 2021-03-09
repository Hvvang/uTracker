//
// Created by Artem Shemidko on 14.02.2021.
//

#ifndef UTRACKER_EDITWORKFLOWRESPONSEHANDLER_H
#define UTRACKER_EDITWORKFLOWRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class EditWorkflowResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit EditWorkflowResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};

#endif //UTRACKER_EDITWORKFLOWRESPONSEHANDLER_H
