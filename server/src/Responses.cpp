#include "Responses.h"


Responses::Responses(QTcpSocket *socket) : m_socket(socket) {}

Responses::~Responses() {}

void Responses::toSignUp() {
    m_socket->write("Succesfully signed up!");
}

//void Responses::toSignIn() {
//
//}

//void Responses::toLogOut() {
//
//}