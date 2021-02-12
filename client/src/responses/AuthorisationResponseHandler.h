//
// Created by Artem Shemidko on 03.02.2021.
//

#ifndef UTRACKER_AUTHORISATIONRESPONSEHANDLER_H
#define UTRACKER_AUTHORISATIONRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class AuthorisationResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit AuthorisationResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

signals:
    void authorised();
};


#endif //UTRACKER_AUTHORISATIONRESPONSEHANDLER_H
