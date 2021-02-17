//
// Created by Artem Shemidko on 16.02.2021.
//

#ifndef UTRACKER_HASH_H
#define UTRACKER_HASH_H


#include <QString>
#include <sstream>
#include "openssl/sha.h"
#include <openssl/bio.h>
#include <openssl/evp.h>

QString mx_hash(const QString& pass, const QString& salt = nullptr);


#endif //UTRACKER_HASH_H
