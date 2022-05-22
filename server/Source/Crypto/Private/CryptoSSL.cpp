//
// Created by Artem Shemidko on 21.05.2022.
//

#include "CryptoSSL.h"
#include <QFile>
#include <qdebug.h>


namespace Helper {
    auto LoadFileData = [](const QString &InPath, const QString &InFileName, const QString &InExtension) -> QByteArray {
        QFile File(InPath + "/" + InFileName + "." + InExtension);
        QByteArray Data;

        if(File.open(QIODevice::ReadOnly)) {
            Data = File.readAll();
            File.close();
        }
        else{
            qWarning() << File.errorString();
        }
        return Data;
    };
}

QSslKey Crypto::SSLKey;
QSslCertificate Crypto::SSLCert;
QSslCertificate Crypto::SSLCACert;

void Crypto::Initialize(const QString &CryptoPath) {
    static bool bEvaluated = false;
    if (bEvaluated)
    {
        qDebug() << "SSL key and certificate has already been initialized!";
        return;
    }
    QByteArray key = Helper::LoadFileData(CryptoPath, SSLPrivateKey, "key");
    QByteArray cert = Helper::LoadFileData(CryptoPath, SSLCertificate, "pem");
    QByteArray cacert = Helper::LoadFileData(CryptoPath, SSLCACertificate, "pem");

    SSLKey = QSslKey(key, QSsl::Rsa,QSsl::Pem,QSsl::PrivateKey,"localhost");
    SSLCert = QSslCertificate(cert);
    SSLCACert = QSslCertificate(cacert);

    qDebug() << "Crypto SSL key and certificate was initialized!";

    bEvaluated = true;
}

