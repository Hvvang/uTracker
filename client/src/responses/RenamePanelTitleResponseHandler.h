//
// Created by Artem Shemidko on 12.03.2021.
//

#ifndef CLIENT_RENAMEPANELTITLERESPONSEHANDLER_H
#define CLIENT_RENAMEPANELTITLERESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class RenamePanelTitleResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit RenamePanelTitleResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;
};

#endif //CLIENT_RENAMEPANELTITLERESPONSEHANDLER_H
