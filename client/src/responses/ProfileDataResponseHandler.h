#ifndef PROFILEDATARESPOSEHANDLER_H
#define PROFILEDATARESPOSEHANDLER_H

#include <AbstractResponseHandler.h>

class ProfileDataResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit ProfileDataResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};


#endif // PROFILEDATARESPOSEHANDLER_H
