#include "authorization.h"
#include <iostream>

Authorization::Authorization(QObject *parent) : QObject(parent) {}

bool Authorization::signInHandler(QString ident, QString password) {
    if (ident == "hello" && password == "123456789")
        std::cout << "Hello" << std::endl;
    return ident == "helslo" && password == "123456789";
}
