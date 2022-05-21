//
// Created by Artem Shemidko on 21.05.2022.
//

#pragma once

#include <QSslKey>
#include <QSslCertificate>

class Crypto {
public:

    static QSslKey SSLKey;
    static QSslCertificate SSLCert;

    static void Initialize(const QString &, const QString &);
};
