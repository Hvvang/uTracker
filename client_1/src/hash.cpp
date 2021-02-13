#include "hash.h"

static std::string to_hex(unsigned char s) {
    std::stringstream ss;
    ss << std::hex << (int) s;
    return ss.str();
}

QByteArray mx_hash(const QString& pass )
{
    QByteArray hash = QCryptographicHash::hash(
            QByteArray::fromRawData((const char*) pass.utf16(), pass.length() * 2),
            QCryptographicHash::Md5
    );
    return hash;
}

//QString mx_hash(const QString& pass, const QString& salt) {
//    QString saltPass = pass + salt;
//    unsigned char hash[SHA256_DIGEST_LENGTH];
//    std::string output = "";
//    std::string hex;
//
//    SHA256_CTX sha256;
//    SHA256_Init(&sha256);
//    SHA256_Update(&sha256, saltPass.toStdString().c_str(), saltPass.size());
//    SHA256_Final(hash, &sha256);
//    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//        hex = to_hex(hash[i]);
//        if (hex.size() == 2)
//            output += hex;
//        else {
//            output += ("0" + hex);
//        }
//    }
//    return QString::fromStdString(output);
//}
