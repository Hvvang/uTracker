#include "authorization.h"
#include <iostream>

Authorization::Authorization(QObject *parent) : QObject(parent)
{
    std::cout << "Hello" << std::endl;
}

Authorization::~Authorization()
{

}
