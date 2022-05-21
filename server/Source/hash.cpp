#include "hash.h"

static std::string to_hex(unsigned char s) {
    std::stringstream ss;
    ss << std::hex << (int) s;
    return ss.str();
}

void digest_message(unsigned char *message, unsigned char **digest, unsigned int *digest_len)
{
    EVP_MD_CTX *mdctx;

    if((mdctx = EVP_MD_CTX_create()) == nullptr)
    {
        //handleErrors();
    }

    if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr))
    {
//        handleErrors();
    }

    if(1 != EVP_DigestUpdate(mdctx, message, strlen(message)))
    {
//        handleErrors();
    }

    if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == nullptr)
    {
//        handleErrors();
    }

    if(1 != EVP_DigestFinal_ex(mdctx, *digest, digest_len))
    {
//        handleErrors();
    }
    EVP_MD_CTX_destroy(mdctx);
}


QString mx_hash(const QString& pass, const QString& salt) {
    QString saltPass = pass + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::string output = "";
    std::string hex;

    SHA256_CTX sha256;
    //SHA256()

    //SHA256_Init(&sha256);
    //SHA256_Update(&sha256, saltPass.toStdString().c_str(), saltPass.size());
    //SHA256_Final(hash, &sha256);
    for (unsigned char i : hash)
    {
        hex = to_hex(i);
        if (hex.size() == 2)
            output += hex;
        else {
            output += ("0" + hex);
        }
    }
    return QString::fromStdString(output);
}
