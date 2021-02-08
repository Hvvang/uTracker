#include "usermanager.h"


UserManager::UserManager(QObject *parent) : QObject(parent), m_user(this)
{
//view.engine();
    QPM_INIT(engine)
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        exit(-1);
    initModules();
    //    connect(this, UserManager::doRequestToServer, reuester) // after request_class connection
}

void UserManager::initModules() const
{
//    qmlRegisterType<Authorization>("Authorization", 1, 0, "m_author");
//    engine.rootContext()setContextProperty("author", &m_author);
    auto root = engine.rootContext();
//    root->setContextProperty()
}
