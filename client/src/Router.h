//
// Created by Artem Shemidko on 04.02.2021.
//

#ifndef UTRACKER_ROUTER_H
#define UTRACKER_ROUTER_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class Router : QObject {
Q_OBJECT

public:
    explicit Router(QObject *root = nullptr);
    void initLoaders(QObject *root);
    bool loadWindow(const QUrl &url);
    bool loadPanel(const QUrl &url);

    static Router* singleton(QObject *root = nullptr);

protected:
    static Router* m_instance;

private:
    QQuickItem *m_windowLoader{nullptr};
    QQuickItem *m_panelLoader{nullptr};

};

#define m_router Router::singleton()

#endif //UTRACKER_ROUTER_H
