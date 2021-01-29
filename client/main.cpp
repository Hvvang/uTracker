#include "client.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Client s;
    s.doConnect();

    return a.exec();
}
