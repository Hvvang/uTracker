#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "{[Debug]}" << std::endl;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    std::cout << "{[Debug]}" << std::endl;
    QGuiApplication app(argc, argv);
    std::cout << "{[Debug]}" << std::endl;
    QQmlApplicationEngine engine;
    std::cout << "{[Debug]}!" << std::endl;
    QPM_INIT(engine)
    std::cout << "!{[Debug]}" << std::endl;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    std::cout << "!!{[Debug]}" << std::endl;
    if (engine.rootObjects().isEmpty()) {
        std::cout << "!!!{[Debug]}" << std::endl;
        return -1;
    }
    std::cout << "{[Debug]}" << std::endl;
    app.quit();
    return app.exec();
}
