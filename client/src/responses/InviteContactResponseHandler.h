#ifndef INVITECONTACTRESPONSEHANDLER_H
#define INVITECONTACTRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class InviteContactResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit InviteContactResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};

#endif // INVITECONTACTRESPONSEHANDLER_H
