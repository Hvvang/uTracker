//
// Created by Artem Shemidko on 15.05.2022.
//

#include "Application.h"
#include <qdebug.h>

#define Path_Join(left, right) left + "/" + right

Application::Application(int argc, char **argv)
    : QCoreApplication(argc, argv)
{
    setOrganizationName("Huang__He");
    setApplicationName("UTrackerServer");
    setApplicationVersion("1.0.0.");

    ApplicationContext::BaseLocation = GetRootDirectory();
    ApplicationContext::ContentLocation = GetContentDirectory();
    ApplicationContext::ConfigLocation = GetConfigDirectory();
    ApplicationContext::DatabaseLocation = GetDatabaseDirectory();

    qDebug() << "AppContext.BaseLocation: " << ApplicationContext::BaseLocation;
    qDebug() << "AppContext.ContentLocation: " << ApplicationContext::ContentLocation;
    qDebug() << "AppContext.ConfigLocation: " << ApplicationContext::ConfigLocation;
    qDebug() << "AppContext.DatabaseLocation: " << ApplicationContext::DatabaseLocation;

    connect(this, &QCoreApplication::aboutToQuit, this, &Application::Exit);
}

Application::~Application() {
    Context().OnApplicationExit();
}


ApplicationContext &Application::Context() {
    return AppContext;
}

QString Application::GetRootDirectory() {
    return applicationDirPath();
}

QString Application::GetConfigDirectory() {
    return Path_Join(GetRootDirectory(), QString("Config"));
}

QString Application::GetContentDirectory() {
    return Path_Join(GetRootDirectory(), QString("Content"));
}

QString Application::GetDatabaseDirectory() {
    return Path_Join(GetContentDirectory(), QString("Database"));
}

int Application::Run() {
    Context().OnApplicationStart();

    return exec();
}

void Application::Exit() {
    Context().OnApplicationExit();

    exit();
}
