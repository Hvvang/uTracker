//
// Created by Artem Shemidko on 22.05.2022.
//

#ifndef UTRACKERSERVER_SSLSOCKET_H
#define UTRACKERSERVER_SSLSOCKET_H

#include <QSslSocket>

class SSLSocket : public QSslSocket {
    Q_OBJECT
public:

    void Initialize();

private slots:

    void OnFatalError();
    void OnErrors(const QList<QSslError> &errors);

signals:

    void FatalError();

private:

};


#endif //UTRACKERSERVER_SSLSOCKET_H
