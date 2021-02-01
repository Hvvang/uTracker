#include "client.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        qDebug() << "usage ./utracker [ip] [post]";
        return 1;
    }
    Client s;
    s.doConnect(argv[1], QString(argv[2]).toInt());

    return a.exec();
}
