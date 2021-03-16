//
// Created by Artem Shemidko on 17.02.2021.
//

#ifndef UTRACKER_GETPANELTASKSRESPONSEHANDLER_H
#define UTRACKER_GETPANELTASKSRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class GetPanelTasksResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit GetPanelTasksResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

private:
    QStringList tagsFromJsonArray(const QJsonArray &jsonValue);
};


#endif //UTRACKER_GETPANELTASKSRESPONSEHANDLER_H
