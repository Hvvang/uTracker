//
// Created by Artem Shemidko on 04.02.2021.
//

#include "Router.h"

#include <qdebug.h>

Router* Router::m_instance = nullptr;

Router::Router(QObject *root)
    : QObject(root) {
    m_windowLoader = root->findChild<QQuickItem *>("windowLoader");
    m_instance = this;
}

void Router::initLoaders(QObject *root) {
    if (root) {
        if (!m_windowLoader)
            m_windowLoader = root->findChild<QQuickItem *>("windowLoader");
        if (!m_panelLoader)
            m_panelLoader = root->findChild<QQuickItem *>("panelLoader");
    }
}

bool Router::loadWindow(const QUrl &url) {
    if (m_windowLoader) {
        m_windowLoader->setProperty("source", url);
        return true;
    }
    return false;
}

bool Router::loadPanel(const QUrl &url) {
    if (m_panelLoader) {
        m_panelLoader->setProperty("source", url);
        return true;
    }
    return false;
}

Router *Router::singleton(QObject *root) {
    if (!m_instance) {
        m_instance = new Router(root);
    }
    return m_instance;
}

