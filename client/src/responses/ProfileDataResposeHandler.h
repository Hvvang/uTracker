#ifndef PROFILEDATARESPOSEHANDLER_H
#define PROFILEDATARESPOSEHANDLER_H

#include <AbstractResponseHandler.h>

class ProfileDataResposeHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit ProfileDataResposeHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};


#endif // PROFILEDATARESPOSEHANDLER_H
