//
// Created by Artem Shemidko on 22.05.2022.
//

#include "SSLSocket.h"
#include "CryptoSSL.h"
#include <QSslConfiguration>
#include <QHostAddress>

void SSLSocket::Initialize() {

    QList<QSslCertificate> listCA;
    listCA.append(Crypto::SSLCACert);
    QSslConfiguration conf;
    conf.setPrivateKey(Crypto::SSLKey);
    conf.setLocalCertificate(Crypto::SSLCert);
    conf.setCaCertificates(listCA);

    setSslConfiguration(conf);

    // Report any SSL errors that occur
    connect(this, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(OnErrors(const QList<QSslError> &)));

    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnFatalError()));

    setPeerVerifyMode(QSslSocket::VerifyPeer);

    startServerEncryption();
}

void SSLSocket::OnFatalError() {
    emit FatalError();
}

void SSLSocket::OnErrors(const QList<QSslError> &errors) {
    QString errorStrings;
    foreach (QSslError error, errors) {
        errorStrings += error.errorString();
        if (error != errors.last()) {
            errorStrings += ';';
        }
    }

    QString Error = QString("[%1] %2:%3 reported the following SSL errors: %4")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz ap"))
            .arg(peerAddress().toString())
            .arg(peerPort())
            .arg(errorStrings);
    qDebug() << Error;
}

