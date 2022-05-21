//
// Created by Artem Shemidko on 15.05.2022.
//

#ifndef SERVER_APPLICATIONCONTEXT_H
#define SERVER_APPLICATIONCONTEXT_H

#include <QObject>
#include <QString>

class ApplicationContext : public QObject {
Q_OBJECT
public:

    typedef void (*StartFallbackPtr)();
    StartFallbackPtr OnApplicationStart = nullptr;

    typedef void (*ExitFallbackPtr)();
    ExitFallbackPtr OnApplicationExit = nullptr;

    static QString BaseLocation;
    static QString DatabaseLocation;
    static QString ContentLocation;
    static QString ConfigLocation;
    static QString DatabaseName;
};


#endif //SERVER_APPLICATIONCONTEXT_H
