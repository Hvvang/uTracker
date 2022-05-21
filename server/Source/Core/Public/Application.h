//
// Created by Artem Shemidko on 15.05.2022.
//

#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <QCoreApplication>
#include "ApplicationContext.h"

class ApplicationContext;

class Application : public QCoreApplication {
public:
    Application(int argc, char *argv[]);
    ~Application() override;

    int Run();
    void Exit();

    ApplicationContext &Context();

    static QString GetRootDirectory();
    static QString GetConfigDirectory();
    static QString GetContentDirectory();
    static QString GetDatabaseDirectory();

private:
    ApplicationContext AppContext;
};


#endif //SERVER_APPLICATION_H
