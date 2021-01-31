#include "client.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Client s;
    if (argc != 3) {
        qDebug() << "usage ./utracker [ip] [post]";
        return 0;
    }
    QString port = argv[2];
    s.doConnect(argv[1], port.toInt());

    return a.exec();
}
