#pragma once

#include <QString>
#include <sstream>

#include <QCryptographicHash>

//#include "openssl/sha.h"
//#include <openssl/bio.h>
//#include <openssl/evp.h>


QByteArray mx_hash(const QString& pass, const QString& salt = nullptr);
