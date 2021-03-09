
//
// Created by Artem Shemidko on 25.02.2021.
//

#ifndef UTRACKER_EDITPANELTITLERESPONSEHANDLER_H
#define UTRACKER_EDITPANELTITLERESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class EditPanelTitleResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit EditPanelTitleResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};


#endif //UTRACKER_EDITPANELTITLERESPONSEHANDLER_H
