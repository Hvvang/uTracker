#ifndef ARCHIVEWORKFLOWRESPONSEHANDLER_H
#define ARCHIVEWORKFLOWRESPONSEHANDLER_H

#include <AbstractResponseHandler.h>

class ArchiveWorkflowResponseHandler : public AbstractResponseHandler {
Q_OBJECT
public:
    explicit ArchiveWorkflowResponseHandler(QObject *parent = nullptr);

    void processResponse(const QByteArray &data) override;

};

#endif // ARCHIVEWORKFLOWRESPONSEHANDLER_H
